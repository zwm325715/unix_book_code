set(LIB_SRCS 
        error.c    
        openmax.c
        pathalloc.c 
        setfl_3.14.c
        prexit_8.6.c
        tellwait_10.16.c
        env.c
        # system_8.13.c
        system_10.18.c
        prmask_10.12.c
        lockreg_14.3.c
    )
#aque对象库
add_library(aque 
            OBJECT
            ${LIB_SRCS} 
            )