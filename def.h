typedef union 
{
	int array[5];
	struct
	{
		struct{
			int a:16;
			int b:16;
		}word32;

		struct{
			int a:4;
			int b:4;
			int c:4;
			int d:4;
			int e:16;
		}word36;

		struct{
			int a:8;
			int b:8;
			int c:8;
			int d:8;
		}word40;

		struct{
			int a:1;
			int a1:1;
			int a2:1;
			int a3:1;
			int a4:1;
			int a5:1;
			int a6:1;
			int a7:1;
			int a8:1;
			int a9:1;
			int a10:1;
			int a11:1;
			int a12:1;
			int a13:1;
			int a14:1;
			int a15:1;
			int b:16;
		}word44;

		int word48;
	}data;
}in_data;

typedef struct
{
	int ret1;
	int ret2;
}out_data;