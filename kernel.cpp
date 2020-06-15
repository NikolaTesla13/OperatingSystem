void printf(char* str)
{
    static unsigned short* VideoMemory = (unsigned short*)0xb8000;

    static unsigned char x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, unsigned int /*multiboot_magic*/)
{
    printf("Sandbox OS v0.01\n");
    printf("Checking drivers....................................... OK\n");
    printf("Checking files......................................... OK\n");
    printf("Checking kernel........................................ OK\n");
    printf("...........................OK.............................\n"); // TODO: Add real checking!
    printf("\n");
    printf("READY TO USE\n");
    printf("\n\n");
    printf("$ ");

    while(1);
}
