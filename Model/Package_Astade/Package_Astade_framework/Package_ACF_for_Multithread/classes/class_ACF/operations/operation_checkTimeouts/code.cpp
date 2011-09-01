//~~ void checkTimeouts() [ACF] ~~

if (!scheduledTimeouts)
	return;

while (sem_wait(&myQueueSemaphore))
    continue;

if (nextRead == nextWrite)
{
	unsigned int now = getTimeTick();
	unsigned int diff = now - lastTime;
	lastTime = now;

	while (scheduledTimeouts && diff)
	{
		if (diff <= my_Timeouts[0].Time)
		{
			my_Timeouts[0].Time -= diff;
			diff = 0;
		}
		else
		{
			diff -= my_Timeouts[0].Time;
			my_Timeouts[0].Time = 0;
		}

		while (scheduledTimeouts && my_Timeouts[0].Time == 0)
		{
			sendTimeoutMessage(my_Timeouts[0].Destination);
			--scheduledTimeouts;
			memmove(&my_Timeouts[0], &my_Timeouts[1], sizeof(my_Timeouts[0]) * scheduledTimeouts);
		}
	}
}

sem_post(&myQueueSemaphore);
