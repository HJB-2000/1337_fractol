// #include "fractol.h"
// void l () 
// {
//     system("leaks a.out");
// }

// void init_garbage(t_garbage **collect)
// {
//     if(*collect)
//         return ;
//     *collect = _malloc(sizeof(t_garbage), false);
// }
// t_garbage **get_head(void)
// {
//     static t_garbage *collect = NULL;
//     return(&collect);
// }
// void *_malloc(size_t size, bool flag_1)
// {
//     // t_garbage **head = get_head();
//     if (flag_1)
//     {
//         // _free();
//         return NULL;
//     }
//     void *instant;
//     instant = malloc(size);
//     if (!instant)
//         return NULL;
//     add_node(instant);
//     return(instant);
// }
    
// // int main(int argc, char **argv)
// // {

// //     if ((2 == argc && !ft_strncmp(argv[1], "mandelbort", 10))
// //         || 4 == argc && !ft_strncmp(argv[1], "julia", 5))
// //     {
// //         //todo
// //     }
// //     else
// //     {
// //         my_putstr("please enter a valide arguments exmples:\n\
// //         \t./farctol mandelbort.\n\
// //         \t./farctol julia <value 1><value 2>\n");
// //     }
// //     return 0;
// // }
// int main()
// {
//     char **h;
//     char *s;
//     h = _malloc(2, false);
//     s = _malloc(20, false);
//     int i = 0;
//     while(i < 20)
//     {
//         s[i] = 'h';
//         i++;
//     }
//     s[i] = '\0';
//     h[1] = s;
//     h[2] = NULL;
//     printf("%s", s);
// }