long long int global_int64 = 0xFAFAFAFAFA;
int global_int = 40;

int fun(){
    int int_num10 = 3 + global_int;
    int rec = fun();
    int int_num16 = 0xFFFF--;
    //long long int int64_num16 = 0xABABABABABAB++;
    int int64_num16 = ++0xABABAB;
    {
        {
            int result1 = int64_num16 / int_num16 * int_num10;
            {
                return result1;
            }
        }
        {
            int i = 1;
            for(i = 0; i < 4; i++){
                int result2 = (--int64_num16 % int_num10) * (int64_num16++ / int64_num16);
                return result2;
            }
            //return result2;
        }
    }
    return int64_num16 > int_num16;
}
int fun2(){
    int a = 0;
    long long int b = 0xFFFFB;
    return a;
    //return b;
    //return a + b;
    return a == b;
}
long long int fun3(){
    int a = 0;
    long long int b = 0xFFFFB;
    return ++a;
    return b;
    return a + b;
    return a == b;
}
int main(){
    int a = fun();
    long long int b = fun();

    a = fun2();
    b = fun2();

    //a = fun3();
    b = fun3();

    //a = test();
    //b = global_int();

    //a = result2;
    //a = c;
    return 0;
}