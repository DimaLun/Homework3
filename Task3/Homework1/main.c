#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>
int dist_int(void* from, void* to) {
    uintptr_t a = (uintptr_t)from; uintptr_t b = (uintptr_t)to;
    uintptr_t d = b - a;
    return (int)d;
}
int main() {
    signed char ch = 25; unsigned char chu = 25; signed short sh = 25; unsigned short shu = 25;
    signed int in = 25; unsigned int inu = 25; signed long lo = 25; unsigned long lou = 25;
    signed long long lolo = 25; unsigned long long lolou = 25; float fl = 2.5f; double db = 2.5;
    signed char* pch = &ch; unsigned char* pchu = &chu; signed short* psh = &sh; unsigned short* pshu = &shu;
    signed int* pin = &in; unsigned int* pinu = &inu; signed long* plo = &lo; unsigned long* plou = &lou;
    signed long long* plolo = &lolo; unsigned long long* plolou = &lolou; float* pfl = &fl; double* pdb = &db;
    printf("%p %p %p %p ", pch, pchu, psh, pshu);
    printf("0 %d %d %d", dist_int(pch, pchu), dist_int(pchu, psh), dist_int(psh, pshu));
    printf("\n%p %p %p %p ", pin, pinu, plo, plou);
    printf("%d %d %d %d", dist_int(pshu, pin), dist_int(pin, pinu), dist_int(pinu, plo), dist_int(plo, plou));
    printf("\n%p %p %p %p ", plolo, plolou, pfl, pdb);
    printf("%d %d %d %d", dist_int(plou, plolo), dist_int(plolo, plolou), dist_int(plolou, pfl), dist_int(pfl, pdb));
    return 0;

    /*То есть между char, unsigned char, short и unsigned short ровно по 32 байта.
    Это намного больше размеров самих типов.
    Значит, компилятор не упаковывает переменные плотно, а выделяет под каждую отдельный слот.

    Здесь снова шаг 32 байта.

    Здесь шаг уже не всегда 32. Это связано с требованиями выравнивания:
    long long и double обычно требуют выравнивания на 8 байт;
    float — на 4 байта;
    адреса plolo, plolou, pdb кратны 8;
    pfl кратен 4, но не 8.
    Поэтому между plolou и pfl получилось 28 байт, а между pfl и pdb — 36.
    Компилятор подбирает такие промежутки, чтобы следующий объект попал на нужную границу выравнивания.*/
}