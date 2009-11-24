static int freqidx;
static int freqcpu[5] = {66, 133, 222, 266, 333};
static int freqbus[5] = {33, 66, 111, 133, 166};

static void layout_buscpu()
{
	if(idx < 0)
		return;
	freqidx = idx;
	if(freqcpu[freqidx] > 222 || freqbus[freqidx] > 111)
	{
		scePowerSetClockFrequency(222, 222, 111);
		scePowerSetCpuClockFrequency(222);
		scePowerSetBusClockFrequency(111);
		scePowerSetClockFrequency(freqcpu[freqidx], freqcpu[freqidx], freqbus[freqidx]);
	}
	else
	{
		scePowerSetClockFrequency(222, 222, 111);
		scePowerSetCpuClockFrequency(222);
		scePowerSetBusClockFrequency(111);
		scePowerSetCpuClockFrequency(freqcpu[freqidx]);
		scePowerSetBusClockFrequency(freqbus[freqidx]);
	}
	sceKernelDelayThread(1000000);
}
