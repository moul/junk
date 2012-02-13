#ifndef _MGS_TIMER_H
# define _MGS_TIMER_H

# define MGS_TIMER_SEC(T)	((int)(T))
# define MGS_TIMER_USEC(T)	((int)((T - MGS_TIMER_SEC(T)) * 1000000))
# define MGS_TIMER_DOUBLE(time) (time.tv_sec + ((double)time.tv_usec / 1000000))

/* timer.c */
double		mgs_time_get(void);

#endif /* !_MGS_TIMER_H */
