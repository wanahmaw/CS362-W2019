

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      System.out.println("\nCorrect URL:");
      System.out.println("http://google.com");
      System.out.println(urlVal.isValid("http://google.com"));
      System.out.println("\nIncorrect URL:");
      System.out.println("ww.google.com");
      System.out.println(urlVal.isValid("ww.google.com"));
      System.out.println("gogle.c");
      System.out.println(urlVal.isValid("gogle.c"));
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   
	   System.out.println("\nTesting Parititon:\n");

	    String[] schemesRegexp = {"http://", "h3tp://", "://", ":/", " "};
	    UrlValidator valForSchemes = new UrlValidator(schemesRegexp, 0);
	    for (int i = 0; i < schemesRegexp.length; i++) {
	      String curScheme = schemesRegexp[i];
	      System.out.println("\nTesting " + curScheme);
	      boolean valid = valForSchemes.isValidScheme(curScheme);
	      if (valid == false && i == 0 || valid == false && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == false && i == 4) {
	        System.out.println("FAILED, invalid scheme\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
