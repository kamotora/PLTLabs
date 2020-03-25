int fun(){
    int a = 0;
    return a + 1 + 2 + 3 + 4 + 5;
    {
        a = a + 10;
        return a;
    }
}

int fun1(){
    int i;
    for(i = 0; i < 100; i++){
        {
            int a, b, c , d , k , l ,m, q, z, x;
        }
    }
    return i;
}
int n = 10, c = 50;
int rec(){
    int a = 1, b = n;
    int i;
    for(i = n - 1; c > 0; i++){
        c = c - 1;
        n = n - 1;
        a = a * rec();
    }
    return a;
}
int rec2(){
    int i;
    for(i = 0; c > 0; i++){
        c = c - 1;
        i = i * rec2();
    }
    return i;
}
int main(){
    int n = 100000;
    int a = fun();
    int b = fun1();
    int c = rec();
    int d = rec2();
    return 0;
}