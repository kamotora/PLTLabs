
int globalInt = 10;

int fun() {
    int fun_a;
    for (fun_a = 0; fun_a <= 5; fun_a++);
    return fun_a - 10 + globalInt;
}

long long global_long_long = 0;

int add1_to_global_long_long() {
    int mem = global_long_long + 1;
    return mem;
}

int test_func_in_for() {
    int i;
    //for(i = 0; i < 10000000; i++){
    for (i = 0; i < 100; i++) {
        global_long_long = add1_to_global_long_long();
    }
    return global_long_long;
}

int main() {
    int res_fun = fun();
    int test_func_in_expr = 2 * (3 * (fun() + 10) / 6);
    long long res_fun2 = test_func_in_for();
    int a = 186, d = 0xBA;
    long long c = -0xBA;
    a = a * 100000 * 100000 * 100000;
    d = d * 100000 * 100000 * 100000;
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

            a = (((l))) * l / (3 + cc * 2 * var) % 0xF * test;
            {
                a = -(a + (a * ((a * test) * a)));
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