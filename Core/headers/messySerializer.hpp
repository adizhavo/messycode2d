#ifndef messySerializer_hpp
#define messySerializer_hpp

#include <string>

// Macros to expose a variable to the editor

#define START_SERIALIZER(s)                     \
    public :                                    \
        int s_size = s;                         \
        SerializedData* s_data[s] {             \

#define SERIALIZE(t, n)                         \
    new SerializedData( #t , #n, &n )           \

#define AND ,

#define END_SERIALIZER                          \
    };                                          \
    SerializedData*GetSerializedData(string id){\
        for (int i=0;i<Size();i++)              \
        if (id.compare(s_data[i]->id) == 0)     \
            return s_data[i];                   \
        return 0;                               \
    }                                           \
    SerializedData** GetSerializedData() {      \
        return s_data;                          \
    }                                           \
    int Size() { return s_size; }               \


namespace MessyCode2D_Engine {
    using namespace std;

    // Data strucure used by the above macros macro to hold serializable variables;
    // supports only strings, flaots, int, bool data type

    struct SerializedData
    {
    public:
        string id;
        string type;
        string* s;
        int* i;
        float* f;
        bool* b;

        SerializedData() {
            s = 0;
            i = 0;
            f = 0;
            b = 0;
        }

        SerializedData(string id, string type, int* i){
            this->id = id;
            this->type = type;
            this->i = i;
            s = 0;
            f = 0;
            b = 0;
        }

        SerializedData(string id, string type, bool* b){
            this->id = id;
            this->type = type;
            this->b = b;
            s = 0;
            i = 0;
            f = 0;
        }

        SerializedData(string id, string type, float* f)
        {
            this->id = id;
            this->type = type;
            this->f = f;
            s = 0;
            i = 0;
            b = 0;
        }

        SerializedData(string id, string type, string* s)
        {
            this->id = id;
            this->type = type;
            this->s = s;
            i = 0;
            f = 0;
            b = 0;
        }
    };

    // Component should inherit this to serialized data

    class MessySerializer
    {
    public:
        virtual SerializedData* GetSerializedData(string id) = 0;
        virtual SerializedData** GetSerializedData() = 0;
        virtual int Size() = 0;
    };
}

#endif
