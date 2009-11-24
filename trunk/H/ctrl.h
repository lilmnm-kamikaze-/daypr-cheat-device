#ifndef _CTRL_H
#define _CTRL_H

extern unsigned int ctrl_read();
extern void ctrl_waitrelease();
extern unsigned int ctrl_waitany();
extern unsigned int ctrl_waitkey(unsigned int keymask);
extern unsigned int ctrl_waitmask(unsigned int keymask);
extern unsigned int ctrl_waittime(unsigned int t);
extern unsigned int ctrl_input();

#endif
