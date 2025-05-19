
extern int testaddfourC(void);
extern void userret2(void);
extern int32 creates(void *, uint32, pri16, char *, uint32, ...);




extern	status	addargs(pid32, int32, int32[], int32,char *, void *);



extern	status	ascdate(uint32, char *);


extern	status	bufinit(void);


extern	pri16	chprio(pid32, pri16);


extern	uint32	clkcount(void);


extern	interrupt clkhandler(void);


extern	void	clkinit(void);


extern	void	clkdisp(void);


extern	syscall	close(did32);


extern	syscall	control(did32, int32, int32, int32);


extern	pid32	create(void *, uint32, pri16, char *, uint32, ...);


extern	void	ctxsw(void *, void *);


extern	void	exit(void);


extern int console_init(void);


extern int remove_irm_protections(void);


extern	int32	initevec(void);
extern	int32	set_evec(uint32, uint32);
extern	void	trap(int32, long *);


extern  void exception(int32, int32*);


extern	syscall	freebuf(char *);


extern	syscall	freemem(char *, uint32);


extern	char	*getbuf(bpid32);


extern	syscall	getc(did32);


extern	pid32	getfirst(qid16);
extern	pid32	getlast(qid16);
extern	pid32	getitem(pid32);


extern	char	*getmem(uint32);


extern	pid32	getpid(void);


extern	syscall	getprio(pid32);


extern	char	*getstk(uint32);


extern	uint64	getticks(void);


extern	status	gettime(uint32 *);


extern	status	getutime(uint32 *);



//extern local int newpidmin(void);

extern pid32 createminpid(void *, uint32, pri16, char *, uint32, ...);
extern pid32 getppid(pid32);


extern	syscall	init(did32);

extern	int32	sizmem(void);


extern	status	insert(pid32, qid16, int32);


extern	status	insertd(pid32, qid16, int32);


extern	uint16	getirmask(void);


extern	intmask	disable(void);
extern	void	enable(void);


extern	devcall	ioerr(void);


extern	devcall	ionull(void);


extern	syscall	kill(pid32);

extern	void	markinit(void);
extern	status	mark(int32 *);

extern	void	*memcpy(void *, const void *, int32);

extern	int32	*memcmp(void *, const void *, int32);


extern  void    *memset(void *, const int, int32);


extern	bpid32	mkbufpool(int32, int32);

extern	qid16	newqueue(void);


extern	syscall	open(did32, char *, char *);


extern	void	panic(char *);


extern	int32	pci_init(void);


extern	void	platinit(void);


extern	syscall	putc(did32, char);


extern	int32	quark_irq_routing(void);


extern	pid32	enqueue(pid32, qid16);
extern	pid32	dequueue(qid16);

extern	syscall	read(did32, char *, uint32);


extern	status	ready(pid32);


extern	umsg32	receive(void);


extern	umsg32	recvclr(void);


extern	umsg32	recvtime(int32);


extern	void	resched(void);
extern	status	resched_cntl(int32);


extern	void	restore(intmask);


extern	pri16	resume(pid32);


extern	syscall	seek(did32, uint32);

extern	syscall	semcount(sid32);


extern	sid32	semcreate(int32);


extern	syscall	semdelete(sid32);

extern	syscall	semreset(sid32, int32);


extern	syscall	send(pid32, umsg32);


extern	syscall	signal(sid32);


extern	syscall	signaln(sid32, int32);


extern	syscall	sleepms(int32);
extern	syscall	sleep(int32);


extern	int32	inb(int32);
extern	int32	inw(int32);
extern	int32	inl(int32);
extern	int32	outb(int32, int32);
extern	int32	outw(int32, int32);
extern	int32	outl(int32, int32);
extern	int32	insw(int32, int32 ,int32);
extern	int32	outsw(int32, int32, int32);
extern	int32	lidt(void);
extern	int32	cpuid(void);


extern	syscall	suspend(pid32);


extern	syscall	unsleep(pid32);


extern	void	userret(void);


extern	syscall	wait(sid32);


extern	void	wakeup(void);


extern	syscall	write(did32, char *, uint32);


extern	void	xdone(void);


extern	syscall	yield(void);

/* NETWORK BYTE ORDER CONVERSION NOT NEEDED ON A BIG-ENDIAN COMPUTER */
#define	htons(x)  ((0xff & ((x)>>8)) | ((0xff & (x)) << 8))
#define	htonl(x)  ((((x)>>24) & 0x000000ff) | (((x)>> 8) & 0x0000ff00) | \
		   (((x)<<8) & 0x00ff0000) | (((x)<<24) & 0xff000000))
#define	ntohs(x)  ((0xff & ((x)>>8)) | ( (0xff & (x)) << 8))
#define	ntohl(x)  ((((x)>>24) & 0x000000ff) | (((x)>> 8) & 0x0000ff00) | \
		   (((x)<<8) & 0x00ff0000) | (((x)<<24) & 0xff000000))
