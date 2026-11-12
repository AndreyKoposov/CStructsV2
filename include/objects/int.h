typedef struct integer {
    long long value;
} Integer;

typedef struct uinteger {
    unsigned long long value;
} UInteger;

void* Int(long long value);
void* UInt(unsigned long long value);