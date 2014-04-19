var firstRow = true;

while(input = readline()) {
  if (firstRow) { print("x" + input.substring(1)); firstRow = false; } 
	else 
	{
		for ( var i = 0, length = input.length; i < length; i++ )
		{
			if ( input.charAt(i) == 'o' )
			{
				 print( input.substring(0, i + 1) 
				 	+ '|x' 
				 	+ input.substring(i + 3, input.length));
			}
		}
		print(input); 
	}
}       