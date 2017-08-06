Simply enter make and then run the driver.

1) The input and output files are in the same folder/directory

2) ALL the test results are not in output file;
   The output file only contains the results of input file
   
   I have done further testing using standard input and standard output.
   The program runs and show the output to standard output for the following:
   1) the examples in the assignment
   2) my own tests of empty polynomials
   3) the tests for copy constructor and assignment operator
   4) also asks for the user if they want to test their own specific polynomial
  
3) addition: + operator has been overloaded and returns a newly created polynomial
			 It means in this equation: c=a+b; a and b won't get changed
   differentiation: this method is used like this- a.differentiateX()
			 It changes the value of the original a. 
			 So, once we differentiate a, we can never get back the original terms of a.
			 However, I have defined another function which is used like this: c= differX(a);
			 This method takes 'a' as parameter and returns a new polynomial 'c'. 
			 Hence, a does not get changed.
	
4) The assignment does not mention whether or not shall we create 
	new polynomials for addition and differentiation.
	So, I have done it both ways for differentiation but 
	addition simply creates a new polynomial rather than merging and changing pointers of original polynomials.
 
5) The way readFile works:
   Create a polynomial p;
   Read number of terms the polynomial will have 
   repeatedly read cof, x, y into p (for each term);
   add p+p; differentiateX; differentiateY; show result
   come out of loop, destroy p
   next iteration starts and repeat from the 2nd step