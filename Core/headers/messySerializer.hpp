#ifndef messySerializer_hpp
#define messySerializer_hpp

#include <string>

// Macros to expose a variable to the editor

#define START_SERIALIZER(s)                     \
    public :                                    \
        int size = s;                           \
        SerializerData* data[s] {               \

#define SERIALIZE(t, n)                         \
    new SerializerData( #t , #n, &n )           \

#define AND ,

#define END_SERIALIZER                          \
    };                                          \
    SerializerData** GetData() {                \
        return data;                            \
    }                                           \
    int Size() { return size; }                 \

namespace MessyCode2D_Engine {
    using namespace std;

    // Data strucure used by the macro to point and serialize components variables

    struct SerializerData
    {
    public:
        string id;
        string name;
        string* s;
        int* i;
        float* f;
        bool* b;

        SerializerData(string id, string name, int* i){
            this->id = id;
            this->name = name;
            this->i = i;
        }

        SerializerData(string id, string name, bool* b){
            this->id = id;
            this->name = name;
            this->b = b;
        }

        SerializerData(string id, string name, float* f)
        {
            this->id = id;
            this->name = name;
            this->f = f;
        }

        SerializerData(string id, string name, string* s)
        {
            this->id = id;
            this->name = name;
            this->s = s;
        }
    };

    // Wrapper to return the data structure, should be inheret from a component

    class MessySerializer
    {
    public:
        virtual SerializerData** GetData() = 0;
        virtual int Size() = 0;
    };
}

#endif
