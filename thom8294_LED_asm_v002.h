

#ifndef THOM8294_LAB2B_ASM_V002_H
#define THOM8294_LAB2B_ASM_V002_H

#define PERIOD 5

#ifdef __cplusplus
extern "C" {
#endif

    void write_0(void);
    void write_1(void);
    void delay_100micro(void);
    void delay_1milli(void);
   
    void delay(int delay_in_ms)
    {
        while (delay_in_ms > 0)
        {
            delay_1milli();
            delay_in_ms--;
        }
    }

    void writeColor(int r, int g, int b)
    {
        // r values
        int i = 8;
        while (i > 0)
        {
            if (((r >> (i - 1)) & 0b00000001) == 1)
            {
                write_1();
            }
            else
            {
                write_0();
            }
            i--;
        }
        // g values
        int j = 8;
        while (j > 0)
        {
            if (((g >> (j - 1)) & 0b00000001) == 1)
            {
                write_1();
            }
            else
            {
                write_0();
            }
            j--;
        }
        int k = 8;
        while (k > 0)
        {
            if (((b >> (k - 1)) & 0b00000001) == 1)
            {
                write_1();
            }
            else
            {
                write_0();
            }
            k--;
        }
    }

#ifdef __cplusplus
}
#endif

#endif	/* THOM8294_LAB2B_ASM_V002_H */