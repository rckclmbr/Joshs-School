void timer::start(void)
{
    QueryPerformanceFrequency(&freq);				// Windows
    QueryPerformanceCounter(&start_time);			// Windows
//     ftime(&startTimeBuffer);						// Other (inaccurate)
//     startMillis = startTimeBuffer.time*1000 + startTimeBuffer.millitm;	// Other (inaccurate)
}

void timer::stop(void)
{
    QueryPerformanceCounter(&end_time);			// Windows
//    ftime(&endTimeBuffer);					// Other (inaccurate)
//    endMillis = endTimeBuffer.time*1000 + startTimeBuffer.millitm;	// Other (Inaccurate)
}

double timer::putTime(void)
{
     return ((end_time.QuadPart - start_time.QuadPart)/(double)freq.QuadPart) * 1000000;    // Windows
	
//	return (endMillis - startMillis);   // Other
}
