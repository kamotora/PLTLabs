int fun(){
    int fun_a = 5;
    return fun_a;
}

int globalInt = 33;

int main() {
    int a = 186, d = 0xBA;
    long long c = -0xBA;
    //int32 10cc
    a = a * 100000 * 100000 * 100000;
    //int32 16cc
    d = d * 100000 * 100000 * 100000;
    //int64 16cc
    c = c * (-1) * 100000 * 100000 * 100000;
    int e = c;
    long long int q;
    q = 1;
    int b = -9;
    long long cc = 0xFFF;
    int l = 1;
    //int l = 5++;
    l = ++l * cc + (5 / (++b)) + globalInt;
    b = b;
    l = l;
    int var = -0xABC;
    {
        long i = 444444;
        {
            int test = 3;

            a = (((l)))*l / (3 + cc * 2 * var) % 0xF * test;
            {
                a = - (a + (a * ((a * test) * a ))) ;
            }
        }
        //a = test + 3;
        {
            int test = 4;
            a = (3 + cc * 2) % 0xF * test / l;
        }
    }
    int testFor = 1;
    int i;
    //for(i = 0; i < 10; i++)
    {
        testFor = testFor + i;
        i = i;
        int j;
        //for(j = 0; j < 10; j++)
        {
            testFor = testFor + j;
            j = j;
        }
    }
    return q;
}