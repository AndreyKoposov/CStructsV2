# vector

Обобщённый динамический массив для C11.

## Сборка

    make            # build/libvector.a
    make test       # запустить тесты (нужен CUnit)
    make asan       # тесты под ASan/UBSan
    make install PREFIX=$HOME/.local

## Использование

    #include <vector.h>

    Vector *v = vector(sizeof(int));
    int x = 42;
    vecpush(v, &x);
    int out;
    vecpop(v, &out);
    vecdes(v);

Линковка:

    gcc main.c -I$PREFIX/include -L$PREFIX/lib -lcstructs

## API

| Функция | Назначение |
|---|---|
| `vector(elem_size)` | создать вектор |
| `vecdes(v)` | уничтожить |
| `vecpush(v, el)` | добавить в конец |
| `vecpop(v, out)` | удалить с конца |
| `vecat(v, i)` | указатель на i-й элемент |
| `vecinsert(v, i, el)` | вставить в позицию |
| `vecerase(v, i)` | удалить по индексу |
| `vecfor(v, fn, ctx)` | обход |
| ... | ... |

## Контракты

- `vecat` возвращает `NULL`, если `i >= size`.
- Указатель из `vecat` действителен до `vecres`/`vecshr`/`vecdes`/`vecpush` при полном capacity.
- Вектор владеет буфером, но не «внутренностями» элементов: если элемент содержит `char *`, освобождай его сам.
- Все функции `NULL`-безопасны (возвращают `-1`/`NULL`).

## Лицензия

MIT