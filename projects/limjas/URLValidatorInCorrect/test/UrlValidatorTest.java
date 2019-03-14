

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
   /* Validates purely valid URLs. Set is simple in interest of time
    * 1st partition only focuses on valid URLs
    * Precondition: N/A
    * Post-condition: All test cases are valid
   */
   public void testYourFirstPartition() {    
        // To be used for building a complete URL
        int i, j, k, l, m;
        StringBuilder urlBuilder = new StringBuilder();
        UrlValidator urlVal;
        String[] scheme = {"http://","ftp://",
                              "h3t://",
                              ""};
       
        String[] authority = {"www.google.com",
                                 "go.com",
                                 "go.au",
                                 "123.com",
                                 "255.255.255.255"};
     
        String[] port = {":10",
                            ":65535",
                            ":0",
                            ""};
       
        String[] path = {"/yay",
                            "/yay1",
                            "/1yay",
                            "/$17",
                            "/yay/",
                            "/yay/yatta"};
       
        String[] query = {"?cat=meow",
                             "?cat=meow&claws=out",
                             ""};
       
        // Creates method that validates all URL schemes
        urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
        System.out.println("\n1st partition: Testing only valid URLs");
       
        // Loops through each part to build an URL. Then we test it
        for (i = 0; i < scheme.length; i++) {
            for (j = 0; j < authority.length; j++) {
                for (k = 0; k < port.length; k++) {
                    for (l = 0; l < path.length; l++) {
                        for (m = 0; m < query.length; m++) {
                            // Reset string
                            urlBuilder.setLength(0);
                            if (! scheme[i].equals(null)) {
                                urlBuilder.append(scheme[i]);
                            }
                            if (! authority[j].equals(null)) {
                                urlBuilder.append(authority[j]);
                            }
                            if (! port[k].equals(null)) {
                                urlBuilder.append(port[k]);
                            }
                            if (! path[l].equals(null)) {
                                urlBuilder.append(path[l]);
                            }
                            if (! query[m].equals(null)) {
                                urlBuilder.append(query[m]);
                            }
                            String finalUrl = urlBuilder.toString();
                            //System.out.println(“\nTesting ” + finalUrl);
                            if (!urlVal.isValid(finalUrl)) {
                                System.out.println(finalUrl);
                            }
                        }
                    }
                }
            }
        }
   }

   
   public void testYourSecondPartition() {    
       // To be used for building a complete URL
       int i, j, k, l, m;
       StringBuilder urlBuilder = new StringBuilder();
       UrlValidator urlVal;
       String[] scheme = {"fake","schemewrongurl",
                             "abcdefg",
                             "hi"};
      
       String[] authority = {"com.google.www",
                                "invalid.url.http",
                                "plastic.trees.are.fake",
                                "canadian.geese.urlfake",
                                "9255.fake.cc"};
    
       String[] port = {"xyz",
                           "z123",
                           "abcd",
                           "wrongurl"};
      
       String[] path = {"@1!@$",
                           "%#$#$#$",
                           "wrongURLpath.http",
                           "~~~12",
                           "abcdWrong1232",};
      
       String[] query = {"!fakequery",
                            "&thisisnotaquery",
                            "()()()"};
      
       // Creates method that validates all URL schemes
       urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      
       System.out.println("\n2nd partition: Testing only invalid URLs");
      
       // Loops through each part to build an URL. Then we test it
       for (i = 0; i < scheme.length; i++) {
           for (j = 0; j < authority.length; j++) {
               for (k = 0; k < port.length; k++) {
                   for (l = 0; l < path.length; l++) {
                       for (m = 0; m < query.length; m++) {
                           // Reset string
                           urlBuilder.setLength(0);
                           if (! scheme[i].equals(null)) {
                               urlBuilder.append(scheme[i]);
                           }
                           if (! authority[j].equals(null)) {
                               urlBuilder.append(authority[j]);
                           }
                           if (! port[k].equals(null)) {
                               urlBuilder.append(port[k]);
                           }
                           if (! path[l].equals(null)) {
                               urlBuilder.append(path[l]);
                           }
                           if (! query[m].equals(null)) {
                               urlBuilder.append(query[m]);
                           }
                           String finalUrl = urlBuilder.toString();
                           //System.out.println(“\nTesting ” + finalUrl);
                           if ( urlVal.isValid(finalUrl)) {
                               System.out.println(finalUrl);
                           }
                       }
                   }
               }
           }
       }
  }
   //You need to create more test cases for your Partitions if you need to 
   // scheme partition
   public void testIsValid() {
     System.out.println("\nSchemes Unit Test");
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
   
   // query Partition
   public void testIsValid2() {
     System.out.println("\nQuery Unit Test:\n");
     String[] queryURLExs = {"?action=read", "?name=ferret", "?color=purple", "", "???Fakeaction"};
     UrlValidator queryVals = new UrlValidator(queryURLExs, 0);
     for (int i = 0; i < queryURLExs.length; i++) {
       String current = queryURLExs[i];
       System.out.println("\nTesting " + current);
       boolean validQuery = queryVals.isValidQuery(current);
       if(validQuery == false && i == 0 || validQuery == true && i == 1 || validQuery == false && i == 2 || validQuery == true && i == 3) {
         System.out.println("FAILED, invalid Query\n");
       } else {
     	System.out.println("PASSED\n");
       }
     }
   }

}
