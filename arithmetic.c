
int pgcd(int a, int b)
{
    int tmp;
    while (b != 0)
    {
        tmp = a % b;

        a = b;
        b = tmp;
    }
    return a;
}

int ppcm(int a, int b)
{
    return a * b / pgcd(a, b);
}