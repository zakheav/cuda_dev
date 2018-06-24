#ifndef STL_H_
#define STL_H_
template<class T>
class vec {
    private:
        int m_total_size;
        T* m_data;

    public:
        int m_size;
        vec();
        void add(T a);
        T get(int i);
        ~vec();
};

template<class T>
vec<T>::vec() {
    m_data = new T[10];
    m_size = 0;
    m_total_size = 10;
    for (int i = 0; i < m_total_size; ++i) {
        m_data[i] = 0;
    }
}

template<class T>
void vec<T>::add(T a) {
    if (m_total_size == m_size) {
        T* temp = m_data;
        m_data = new T[m_size * 2];
        for (int i = 0; i < m_size; ++i) {
            m_data[i] = temp[i];
        }
        m_total_size = m_size * 2;
        delete[] temp;
    }
    m_data[m_size] = a;
    ++(m_size);
}

template<class T>
T vec<T>::get(int i) {
    return m_data[i];
}

template<class T>
vec<T>::~vec() {
    delete[] m_data;
}


#endif
