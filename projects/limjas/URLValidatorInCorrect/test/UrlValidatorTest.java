
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.ThreadLocalRandom;

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
                            //System.out.println("\nTesting ” + finalUrl);
                            if (!urlVal.isValid(finalUrl)) {
                                System.out.println(finalUrl);
                            }
                        }
                    }
                }
            }
        }
   }

   /*
   * 2nd partition only focuses on invalid URLs
   * Precondition: N/A
   * Post-condition: All test cases are invalid
  */
   
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
                           //System.out.println("\nTesting ” + finalUrl);
                           if ( urlVal.isValid(finalUrl)) {
                               System.out.println(finalUrl);
                           }
                       }
                   }
               }
           }
       }
  }
   /*
   * 3rd partition random partition focuses on randomization of combinations
   * Precondition: N/A
   * Post-condition: All test cases are valid
  */
   public void testYourThirdPartitionRandom() {
	      StringBuilder urlBuilder = new StringBuilder();
	      UrlValidator urlVal;
	      String[] scheme = {"http://", // true
	              "3ht://", // false
	              "ftp://", // true
	              "h3t://", // true
	              "http/"}; // false
//	      String[] authority1 = {"www.google.com"}; // false
	      String[] authority = {"com.asdf.www", // false
	              "asdf.com", // true
	              "invalid.url.http", // false
	              "255.255.255.255", // true
	              "this.is.invalid", // false
	              "www.apple.com", // true
	              "happy.asdf.doesntwork", // false
	              ".bbb"}; // false
	      String[] port = {"", // true
	              "b1234", // false
	              ":0", // true
	              "badport"}; // false
	      String[] path = {"@$%%dontwork", // false
	              "/happy3/", // true
	              "/hi//", // false
	              "/works5", // true
	              "/$777", // true
	               "/.."}; // false
	      String[] query = {"%wrongquery", // false
	              "?action=view", // true
	              "&queryisfalse", // false
	              ""}; // true
	      // Creates method that validates all URL schemes
	      urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	      System.out.println("\nTesting valid and invalid Urls by building URL through use of random number generator");
	      for (int cases = 1; cases < 101; cases++) {
	         System.out.println("\ntest case #" + cases);
	         // generate random numbers https://stackoverflow.com/questions/363681/how-do-i-generate-random-integers-within-a-specific-range-in-java
	         int randomScheme = ThreadLocalRandom.current().nextInt(0, 4 + 1);
	         int randomAuthority = ThreadLocalRandom.current().nextInt(0, 7 + 1);
	         int randomPort = ThreadLocalRandom.current().nextInt(0, 3 + 1);
	         int randomPath = ThreadLocalRandom.current().nextInt(0, 5 + 1);
	         int randomQuery = ThreadLocalRandom.current().nextInt(0,  3 + 1);
	         // reset url string
	         urlBuilder.setLength(0);
	         // append random scheme, authority, port, path, then query
	         urlBuilder.append(scheme[randomScheme]);
	         urlBuilder.append(authority[randomAuthority]);
	         urlBuilder.append(port[randomPort]);
	         urlBuilder.append(path[randomPath]);
	         urlBuilder.append(query[randomQuery]);
	         // save the randomly built Url to finalUrl
	         String finalUrl = urlBuilder.toString();
	         System.out.println(finalUrl);
	         if (randomScheme == 1 || randomScheme == 4) {
	            System.out.println("scheme is: " + scheme[randomScheme]);
	            System.out.println("scheme should be invalid");
	         }
	         else {
	            System.out.println("scheme is: " + scheme[randomScheme]);
	            System.out.println("scheme should be valid");
	         }
//	           System.out.println("authority is: " + authority1[0]);
//	           System.out.println("authority should be valid");
	         if (randomAuthority == 0 || randomAuthority == 2 || randomAuthority == 4 || randomAuthority == 6 || randomAuthority == 7) {
	            System.out.println("authority is: " + authority[randomAuthority]);
	            System.out.println("authority should be invalid");
	         }
	         else {
	            System.out.println("authority is: " + authority[randomAuthority]);
	            System.out.println("authority should be valid");
	         }
	         if (randomPort == 1 || randomPort == 3) {
	            System.out.println("port is: " + port[randomPort]);
	            System.out.println("port should be invalid");
	         }
	         else {
	            System.out.println("port is: " + port[randomPort]);
	            System.out.println("port should be valid");
	         }
	         if (randomPath == 0 || randomPath == 2 || randomPath == 5) {
	            System.out.println("path is: " + path[randomPath]);
	            System.out.println("path should be invalid");
	         }
	         else {
	            System.out.println("path is: " + path[randomPath]);
	            System.out.println("path should be valid");
	         }
	         if (randomQuery == 0 || randomQuery == 2) {
	            System.out.println("query is: " + query[randomQuery]);
	            System.out.println("query should be invalid");
	         }
	         else {
	            System.out.println("query is: " + query[randomQuery]);
	            System.out.println("query should be valid");
	         }
	         System.out.println(urlVal.isValid(finalUrl));
	      }
	   }
    /* Validates URLs from a file supplied by azadi’s Github Repo
    * https://github.com/citizenlab/test-lists/blob/master/lists/ae.csv
    * Precondition: N/A
    * Post-condition: Gets the URL from a CSV file and validates
    */
 public void testFromFile() {

        // Cited implementation for CSV/txt reader https://www.mkyong.com/java/how-to-read-and-parse-csv-file-in-java/
        String file, line, delimiter;
        UrlValidator urlVal;
       
        System.out.println("Programming based testing via URLS from CSV file");
       
        // Setup
        delimiter = ",";
        file = "url.txt";
        urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
        // Make sure we can open the file and use a buffered reader
        try (BufferedReader buff = new BufferedReader(new FileReader(file))) {
           
            // Grab line if it’s readable and parse for the URL
            while ((line = buff.readLine()) != null) {
               
                String url = line.split(delimiter)[0];    // Get url from CSV
               
                System.out.println("\nTesting " + url);
                if (! urlVal.isValid(url)) {        // Print false when invalid
                    System.out.println("False");
                }
            }
        } catch (IOException e) {    // Catch error if we can’t open file
            System.out.println("Can’t open file");
            e.printStackTrace();
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
