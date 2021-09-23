#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
#include <exception>
#include <type_traits>
#include "Exception.h"

// Dichiarazione incompleta
template <typename T> class Queue;
// Dichiarazione incompleta
template <typename T> std::ostream& operator<<(std::ostream&, const Queue<T>&);

template <typename T>
class Queue {
  protected:
    class Nodo;
    class SmartP {
      public:
        Nodo* punt;
        SmartP(Nodo* p = nullptr) : punt(p) { if(punt) punt->riferimenti++; }
        SmartP(const SmartP& s) : punt(s.punt) { if(punt) punt->riferimenti++; };
        ~SmartP();
        SmartP& operator=(const SmartP&);
        Nodo& operator*() const { return *punt; }
        Nodo* operator->() const { return punt; }
        bool operator==(const SmartP& s) const { return punt == s.punt; }
        bool operator!=(const SmartP& s) const { return !(punt == s.punt); }
    };
    class Nodo {
      public:
        Nodo(const T& t = T(), const SmartP& n = nullptr, const SmartP& p = nullptr) : info(t), next(n), prec(p), riferimenti(0) {}
        Nodo(const Nodo& n) : info(n.info), next(n.next), prec(n.prec), riferimenti(n.riferimenti) {}
        ~Nodo() {};
        T info;
        SmartP next, prec;
        unsigned int riferimenti;
    };
    template <bool C = true>
    class Base_Iterator {
      friend class Queue<T>;
      private:
        Nodo* iter;
        typedef typename std::conditional<C, const T, T>::type value_type;
      public:
        Base_Iterator() : iter(nullptr) {}
        Base_Iterator(const Base_Iterator<false>& b) : iter(b.iter) {}
        Base_Iterator operator++(int);
        Base_Iterator operator--(int);
        Base_Iterator& operator++();
        Base_Iterator& operator--();
        Base_Iterator& operator=(const Base_Iterator& b);
        bool operator==(const Base_Iterator& b) const { return iter == b.iter; }
        bool operator!=(const Base_Iterator& b) const { return !(iter == b.iter); }
        value_type& operator*() const { return iter->info; }
        value_type* operator->() const { return &iter->info; }
    };

    SmartP first;
    SmartP last;

  public:
    // Iteratori
    typedef Base_Iterator<false> iterator;
    typedef Base_Iterator<true> const_iterator;
    // Costruttore
    Queue() : first(nullptr), last(nullptr) {};
    // Operatori
    template <bool C> T& operator[](const Base_Iterator<C>& b) const { return b.iter->info; };
    T& operator[](unsigned int) const;
    // Metodi
    unsigned int size() const;
    bool empty() const { return size() == 0; }
    iterator begin() const;
    iterator lastElem() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    template <bool C> iterator insert(const Base_Iterator<C>&, const T&);
    template <bool C> iterator erase(const Base_Iterator<C>&);
    iterator search(const T&) const;
    iterator indexToIter(int);
    void clear();
    void push_back(const T&);
    T& pop_back();
    void push_front(const T&);
    T& pop_front();
    bool operator==(const Queue<T>&) const;
    bool operator!=(const Queue<T>&) const;
    friend std::ostream& operator<< <T>(std::ostream&, const Queue<T>&);
};

/* Metodi di SmartP */

// Distruttore
template <typename T>
Queue<T>::SmartP::~SmartP() {
  if(punt) {
    punt->riferimenti--;
    if(!punt->riferimenti) { delete punt; }
  }
}

// Oeratore di assegnazione
template <typename T>
typename Queue<T>::SmartP& Queue<T>::SmartP::operator=(const SmartP& s) {
  if(this != &s) {
    Nodo *t = punt;
    punt = s.punt;
    if(punt) punt->riferimenti++;
    if(t) {
      t->riferimenti--;
      if(!t->riferimenti) delete t;
    }
  }
  return *this;
}

/* Metodi di Base_Iterator */

// Operatore di incremento prefisso
template <typename T>
template <bool C>
typename Queue<T>::template Base_Iterator<C>& Queue<T>::Base_Iterator<C>::operator++() {
  if(iter != 0) iter = (iter->next).punt;
  return *this;
}

// Operatore di incremento postfisso
template <typename T>
template <bool C>
typename Queue<T>::template Base_Iterator<C> Queue<T>::Base_Iterator<C>::operator++(int) {
  const Base_Iterator<C> aux(*this);
  if(iter != 0) iter = (iter->next).punt;
  return aux;
}

// Operatore di decremento prefisso
template <typename T>
template <bool C>
typename Queue<T>::template Base_Iterator<C>& Queue<T>::Base_Iterator<C>::operator--() {
  if(iter != 0) iter = (iter->prec).punt;
  return *this;
}

// Operatore di decremento postfisso
template <typename T>
template <bool C>
typename Queue<T>::template Base_Iterator<C> Queue<T>::Base_Iterator<C>::operator--(int) {
  const Base_Iterator<C> aux(*this);
  if(iter != 0) iter = (iter->prec).punt;
  return aux;
}

// Operatore di assegnazione
template <typename T>
template <bool C>
typename Queue<T>::template Base_Iterator<C>& Queue<T>::Base_Iterator<C>::operator=(const Base_Iterator<C>& b) {
  if(this != &b) iter = b.iter;
  return *this;
}

/* Metodi di Queue */

// Dimensione della coda
template <typename T>
unsigned int Queue<T>::size() const {
  unsigned int i = 0;
  for(auto it = begin(); it != end(); ++it) ++i;
  return i;
}

template <typename T>
bool Queue<T>::operator==(const Queue<T>& q) const { return first == q.first; }

template <typename T>
bool Queue<T>::operator!=(const Queue<T>& q) const { return first != q.first; }

template <typename T>
T& Queue<T>::operator[](unsigned int n) const {
  const_iterator it;
  for(it = begin(); it != end() && n > 0; ++it, --n) {}
  return (it.iter)->info;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::begin() const {
  iterator aux;
  aux.iter = first.punt;
  return aux;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::lastElem() const {
  iterator aux;
  aux.iter = last.punt;
  return aux;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::end() const {
  iterator aux;
  aux.iter = nullptr;
  return aux;
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::cbegin() const {
  const_iterator aux;
  aux.iter = first.punt;
  return aux;
}

template <typename T>
typename Queue<T>::const_iterator Queue<T>::cend() const {
  const_iterator aux;
  aux.iter = nullptr;
  return aux;
}

template <typename T>
template <bool C>
typename Queue<T>::iterator Queue<T>::insert(const Queue<T>::Base_Iterator<C>& it, const T& item) {
  if(first == nullptr || it.iter == first.punt) {
    push_front(item);
    return begin();
  } else if(it.iter == nullptr) {
    push_back(item);
    iterator aux;
    aux.iter = last.punt;
    return aux;
  } else {
    SmartP out = first, in;
    iterator aux;
    while(out != nullptr && !(it.iter == out.punt)) out = out->next;
    if(out == nullptr) throw Err_Bad_Iterator("A bad iterator was provided");
    in = new Nodo(item, out, out->prec);
    (out->prec)->next = in;
    out->prec = in;
    aux.iter = in.punt;
    return aux;
  }
}

template <typename T>
template <bool C>
typename Queue<T>::iterator Queue<T>::erase(const Queue<T>::Base_Iterator<C>& it) {
  if(!empty()) {
    if(it.iter == first.punt) {
      pop_front();
      return begin();
    } else if(it.iter == last.punt) {
      pop_back();
      iterator aux;
      aux.iter = last.punt;
      return aux;
    } else {
      SmartP del = first;
      iterator aux;
      while(del != nullptr && !(it.iter == del.punt)) del = del->next;
      if(del == nullptr) throw Err_Bad_Iterator("A bad iterator was provided");
      else {
        SmartP prec = del->prec, next = del->next;
        del->prec = del->next = nullptr;
        prec->next = next;
        next->prec = prec;
        aux.iter = next.punt;
        return aux;
      }
    }
  } else throw Err_Empty_Queue();
}

template <typename T>
typename Queue<T>::iterator Queue<T>::search(const T& key) const {
  iterator it;
  for( it = begin(); it != end() && !(it.iter->info == key); ++it) {}
  if(it == end()) return end();
  return it;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::indexToIter(int n){
  iterator it;
  for( it = begin(); it!=end() && n>0; ++it, --n){}
  return it;
}

template <typename T>
void Queue<T>::clear() {
  if(!empty()) {
    if(first != nullptr) while(first != nullptr) pop_front();
  }
}

template <typename T>
void Queue<T>::push_back(const T& item) {
  if(last == nullptr) first = last = new Nodo(item);
  else {
    last->next = new Nodo(item, nullptr, last);
    last = last->next;
    }
}

template <typename T>
T& Queue<T>::pop_back() {
  if(!empty()) {
    if(last->prec == nullptr) {
      T& aux = (last.punt)->info;
      first = last = nullptr;
      return aux;
    }
    else {
      T& aux = (last.punt)->info;
      (last->prec)->next = nullptr;
      last = last->prec;
      return aux;
    }
  } else throw Err_Empty_Queue();
}

template <typename T>
void Queue<T>::push_front(const T& item) {
  if(first == nullptr) first = last = new Nodo(item);
  else {
    first->prec = new Nodo(item, first);
    first = first->prec;
  }
}

template <typename T>
T& Queue<T>::pop_front() {
  if(!empty()) {
    if(first->next == nullptr) {
      T& aux = (first.punt)->info;
      first = last = nullptr;
      return aux;
    } else {
      T& aux = (first.punt)->info;
      (first->next)->prec = nullptr;
      first = first->next;
      return aux;
    }
  } else throw Err_Empty_Queue();
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q) {
  if(!q.empty()) {
    os << q.size() << " elementi memorizzati:\n" << std::endl;
    int i = 1;
    for(typename Queue<T>::const_iterator it = q.begin(); it != q.end(); ++it) {
      os << i++ << ") " << q[it] << std::endl;
    }
  } else os << "Nessun elemento memorizzato" << std::endl;
  return os;
}

#endif // Queue_H
