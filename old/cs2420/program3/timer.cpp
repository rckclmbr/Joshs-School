
void timer::start(void)
{
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start_time);
    // ftime(&startTimeBuffer);
    //startMillis = startTimeBuffer.time*1000 + startTimeBuffer.millitm;
}

void timer::stop(void)
{
    QueryPerformanceCounter(&end_time);
    // ftime(&endTimeBuffer);
    //endMillis = endTimeBuffer.time*1000 + startTimeBuffer.millitm;
}

double timer::putTime(void)
{
    return ((end_time.QuadPart - start_time.QuadPart)/(double)freq.QuadPart) * 1000000;
}
