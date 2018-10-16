
	void readDataFromFile()
	{
		FILE *binaryFile;
		char buff;
		
		binaryFile = fopen("FILE LOCATION HERE", "rb");
		if (!binaryFile) /* binary file does not exist */
		{
			printf("Unable to open the file as it does not exist");
			return;
		}
		
		/* some code below I think might help get us the size of the file */
		fseek(binaryFile, 0, SEEK_END);
		length = ftell(binaryFile);
		buffer = length;
		
		
		
		if(length/12 != 0)
		{
			printf("invalid file");
			return;
		}
		
		for(int i=0;i<length;i++)
		{
		for(int i=0;i<12;i++)
		{
		int digit = fgetc( FILE * binaryFile );
		if (digit != 0 && digit != 1)
		{
			printf("invalid file");
			return;
		}
		else
		{
			// ADD DIGIT TO ITEM IN ARRAY
		}
		
		
		}
		
		
		}
		fclose(binaryFile);
	}
		