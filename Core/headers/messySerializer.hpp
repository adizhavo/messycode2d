#ifndef messySerializer_hpp
#define messySerializer_hpp

#include <string>

// Macros to expose a variable to the editor

#define START_SERIALIZER(s)                     \
    public :                                    \
        int s_size = s;                         \
        SerializerData* s_data[s] {             \

#define SERIALIZE(t, n)                         \
    new SerializerData( #t , #n, &n )           \

#define AND ,

#define END_SERIALIZER                          \
    };                                          \
    SerializerData* GetSData(string name) {     \
        for (int i=0;i<Size();i++)              \
        if (name.compare(s_data[i]->name) == 0) \
            return s_data[i];                   \
        return 0;                               \
    }                                           \
    SerializerData** GetSData() {               \
        return s_data;                          \
    }                                           \
    int Size() { return s_size; }               \


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

        SerializerData() {
            s = 0;
            i = 0;
            f = 0;
            b = 0;
        }

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
        virtual SerializerData* GetSData(string name) = 0;
        virtual SerializerData** GetSData() = 0;
        virtual int Size() = 0;
    };
}

#endif
