int main(const int argc, const char* argv[])
{
	/*
 	* Return Value : 0 - Job done.
 	*			     1 - Not finished and will be called later.
 	*				 Others - Error code.
 	*/
	extern int start_din();

	return start_din();
}