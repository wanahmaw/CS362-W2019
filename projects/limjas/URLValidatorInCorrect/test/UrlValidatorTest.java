

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
   // scheme partition
   public void testYourFirstPartition() {
     System.out.println("\nSchemes Partitioning Test");
     String[] schemeURLExs = {"http://", "ftp://", "mailto:", "fake://", " "}; //https, ftp, mailto, file, data, and irc
     UrlValidator schemeVals = new UrlValidator(schemeURLExs, 0);
     for (int i = 0; i < schemeURLExs.length; i++) {
       String current = schemeURLExs[i];
       System.out.println("\nTEST: " + current);
       boolean validScheme = schemeVals.isValidScheme(current);
       if (validScheme == false && i == 0 || validScheme == false && i == 1 || validScheme == true && i == 2 || validScheme == true && i == 3 || validScheme == false && i == 4) {
         System.out.println("FAILED, invalid scheme\n");
       } else {
     	System.out.println("PASSED\n");
       }
     }
   }
   
   // authority partition
   public void testYourSecondPartition() {
     System.out.println("\nAuthority Test");
     String[] authorityURLExs = {"www.example.com", "www.yahoo.com", " ", "www.amazon.com"};
     UrlValidator authVal = new UrlValidator(authorityURLExs, 0);
     for (int i = 0; i < authorityURLExs.length; i++) {
       String current = authorityURLExs[i];
       System.out.println("\nTesting: " + current);
       boolean validAuthority = authVal.isValidAuthority(current);
       if (validAuthority == false && i == 0 || validAuthority == true && i == 1 || validAuthority == true && i == 2 || validAuthority == true && i == 3 || validAuthority == true && i == 4) {
         System.out.println("FAILED, invalid authority\n");
       } else {
     	System.out.println("PASSED\n");
       }
     }
   }


   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
