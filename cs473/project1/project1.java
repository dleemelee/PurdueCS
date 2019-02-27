import java.lang.Runtime;
import java.lang.ProcessBuilder;
import java.io.*;
import java.util.HashMap;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Collections;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;

public class project1 {
  static int NUMDOCS=3204;
  public static void part1(String index, String query) {
    try{
      //part1a
      //ProcessBuilder partA = new ProcessBuilder("galago", "build", index, "--inputPath=./corpus");
      //partA.start();

      //partb
      ProcessBuilder partB = new ProcessBuilder("galago", "batch-search", "--requested=5", index, "--query=\'"+query+"\'");
      partB.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      //partB.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      partB.redirectError(new File("err.txt"));
      Process p = partB.start();
      p.waitFor();
     
      /* 
      String cmd[] = {"galago", "batch-search", "--requested=5", index, "--query=\'information retrieval\'"};
      Process p = Runtime.getRuntime().exec(cmd);
      BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
      String s = null;
      while((s=stdInput.readLine())!=null) {
        System.out.print(s);
      }
      System.out.println();
      */

      //practice
      //ProcessBuilder temp = new ProcessBuilder("echo", "helloworld");
      //temp.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      //temp.start();

    } catch(Exception e) {
      e.printStackTrace();
    } 
  }

  public static void part2(String corp_index) {
    //part2a
    try{
      Process p;
      ProcessBuilder dnl = new ProcessBuilder("galago", "dump-name-length", corp_index);
      dnl.redirectOutput(new File("out2dnl.txt"));
      p = dnl.start();
      p.waitFor();
      

      System.out.print("Total Number of Documents: ");
      ProcessBuilder partA = new ProcessBuilder("/bin/sh", "-c",  "cat out2dnl.txt | wc -l"); 
      partA.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      p = partA.start();
      p.waitFor();

      ProcessBuilder dts = new ProcessBuilder("galago", "dump-term-stats", "project1-index/postings.krovetz");
      dts.redirectOutput(new File("out2dts.txt"));
      p = dts.start();
      p.waitFor();
      
      System.out.print("Number of Unique Terms");
      ProcessBuilder partB = new ProcessBuilder("/bin/sh", "-c", "cat out2dts.txt | wc -l");
      partB.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      p = partB.start();
      p.waitFor();

      System.out.print("Lowest Length Document(ID NAME LENGTH):");
      ProcessBuilder partCmin = new ProcessBuilder("/bin/sh", "-c", "awk \'NR == 1 {line = $0; min = $3} NR > 1 && $3 < min {line = $0; min = $3} END{print line}\' out2dnl.txt");
      partCmin.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      p = partCmin.start();
      p.waitFor();
     
      System.out.print("Highest Length Document(ID NAME LENGTH):");
      ProcessBuilder partCmax = new ProcessBuilder("/bin/sh", "-c", "awk \'NR == 1 {line = $0; max = $3} NR > 1 && $3 > max {line = $0; max = $3} END{print line}\' out2dnl.txt");
      partCmax.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      p = partCmax.start();
      p.waitFor();

    } catch(IOException e) {
      e.printStackTrace();
    } catch(InterruptedException ie) {
      ie.printStackTrace();
    }

  }

  public static void printTermFreq(String term) {
    try{

      Process p; 
      
      ProcessBuilder dts = new ProcessBuilder("galago", "dump-term-stats", "project1-index/postings.krovetz");
      dts.redirectOutput(new File("out2dts.txt"));
      p = dts.start();
      p.waitFor();


      ProcessBuilder partD = new ProcessBuilder("/bin/sh", "-c", "cat out2dts.txt | grep \"\\<"+term+"\\>\"");
      partD.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      p = partD.start();
      p.waitFor();
      
      
      
    } catch(IOException e) {
      e.printStackTrace();
    } catch(InterruptedException ie) {
      ie.printStackTrace();
    }
  }

  public static double cosSim(double[] doc, double[] query) {
    double dotProduct = 0.0;
    double normDoc = 0.0;
    double normQuery = 0.0;
    
    for(int i = 0; i < doc.length; i++) {
      dotProduct += doc[i] * query[i];
      normDoc += Math.pow(doc[i],2);
      normQuery += Math.pow(query[i],2);
    }
    //System.out.print("this is: " + normDoc + "  " + normQuery + "  "+ dotProduct+ "  ");
    return dotProduct/(Math.sqrt(normDoc)*Math.sqrt(normQuery));
  }


  public static double tfIDF(String query, int doc) {
    double[] qTFIDF = {0.0};
    double[] dTFIDF = {0.0};
    try{
      int totalWordsDoc = 0;
      Process p;
      ProcessBuilder partF = new ProcessBuilder("galago", "dump-doc-terms", "--index=./project1-index/postings.krovetz", "--iidList="+doc+",");
      partF.redirectOutput(new File("out2ddt.txt"));
      p = partF.start();
      p.waitFor();

      String[] vector = query.split(" ");
      HashMap<String, Integer> myMapTF = new HashMap<String, Integer>();
      HashMap<String, Integer> myMapIDF = new HashMap<String, Integer>();
      File f = new File("grepddt.txt");
      File f1 = new File("grepdts.txt");
      f.delete();
      f.createNewFile();
      ProcessBuilder termCount = new ProcessBuilder("/bin/sh", "-c", "cat out2ddt.txt | grep \"\\<Term Count\\>\"");
      termCount.redirectOutput(ProcessBuilder.Redirect.appendTo(f));
      p = termCount.start();
      p.waitFor();

      for(String word : vector) {
        ProcessBuilder temp = new ProcessBuilder("/bin/sh", "-c", "cat out2ddt.txt | grep \"\\<"+word+"\\>\"");
        //temp.redirectOutput(f);
        temp.redirectOutput(ProcessBuilder.Redirect.appendTo(f));
        p = temp.start();
        p.waitFor();

        ProcessBuilder temp1 = new ProcessBuilder("/bin/sh", "-c", "cat out2dts.txt | grep \"\\<"+word+"\\>\"");
        temp1.redirectOutput(ProcessBuilder.Redirect.appendTo(f1));
        p = temp1.start();
        p.waitFor();
        myMapTF.put(word, 0);
        myMapIDF.put(word,0);
      }
      File file = new File("grepddt.txt");
      FileReader fileReader = new FileReader(file);
      BufferedReader bufferedReader = new BufferedReader(fileReader);
      String line;
      int i = 0;
      int[] qtf = new int[vector.length];
      int[] dtf = new int[vector.length];
      while((line = bufferedReader.readLine())!=null) {
        String[] s;
        if(i == 0) {
          s = line.split(" ");
          boolean flag = false;
          for(String word: s) {
            if(flag == true) {
              //System.out.println("hi"+word.indexOf("\t"));
              totalWordsDoc = Integer.parseInt(word.substring(0,word.indexOf("\t")));
              break;
            }
            if(word.equals("Words:")) {
              flag = true;
            }
          }
          //System.out.println("totalWords:" +totalWordsDoc);
        }
        else {
          s = line.split(",");
          String curr = s[0].substring(s[0].indexOf("\t")+1);
          myMapTF.put(curr, s.length-2);
          //System.out.println(myMapTF.get(curr));
        }
        i++;
      }

      fileReader = new FileReader(f1);
      bufferedReader = new BufferedReader(fileReader);
      while((line = bufferedReader.readLine())!=null) {
        String[] s = line.split("\t");
        myMapIDF.put(s[0], Integer.parseInt(s[2]));
      }
      qTFIDF = new double[vector.length];
      dTFIDF = new double[vector.length];
      double TF = 0;
      double IDF = 0;
      i = 0;
      for(String word: vector) {
        TF = Math.log(1+myMapTF.get(word))/Math.log(2);
        IDF = Math.log((NUMDOCS+0.5)/(myMapIDF.get(word)+0.5))/Math.log(2);
        dTFIDF[i] = TF*IDF;
        TF = Math.log(1+1)/Math.log(2);
        qTFIDF[i] = TF*IDF;
        //System.out.println(word + " " +dTFIDF[i] + " "+ qTFIDF[i]);
        i++;
      }
      
      

    } catch(IOException e) {
      e.printStackTrace();
    } catch(InterruptedException ie) {
      ie.printStackTrace();
    }
    return cosSim(qTFIDF, dTFIDF);
  }

  public static double RSV(String query, int doc) {
    double[] qTFIDF = {0};
    double[] dTFIDF = {0};
    try {
      int totalWordsDoc = 0;
      Process p;
      ProcessBuilder partF = new ProcessBuilder("galago", "dump-doc-terms", "--index=./project1-index/postings.krovetz", "--iidList="+doc+",");
      partF.redirectOutput(new File("out2ddt.txt"));
      p = partF.start();
      p.waitFor();

      String[] vector = query.split(" ");
      HashMap<String, Integer> myMapTF = new HashMap<String, Integer>();
      HashMap<String, Integer> myMapIDF = new HashMap<String, Integer>();
      File f = new File("grepddt.txt");
      File f1 = new File("grepdts.txt");
      f.delete();
      f.createNewFile();
      ProcessBuilder termCount = new ProcessBuilder("/bin/sh", "-c", "cat out2ddt.txt | grep \"\\<Term Count\\>\"");
      termCount.redirectOutput(ProcessBuilder.Redirect.appendTo(f));
      p = termCount.start();
      p.waitFor();

      for(String word : vector) {
        ProcessBuilder temp = new ProcessBuilder("/bin/sh", "-c", "cat out2ddt.txt | grep \"\\<"+word+"\\>\"");
        //temp.redirectOutput(f);
        temp.redirectOutput(ProcessBuilder.Redirect.appendTo(f));
        p = temp.start();
        p.waitFor();

        ProcessBuilder temp1 = new ProcessBuilder("/bin/sh", "-c", "cat out2dts.txt | grep \"\\<"+word+"\\>\"");
        temp1.redirectOutput(ProcessBuilder.Redirect.appendTo(f1));
        p = temp1.start();
        p.waitFor();
        myMapTF.put(word, 0);
        myMapIDF.put(word,0);
      }
      File file = new File("grepddt.txt");
      FileReader fileReader = new FileReader(file);
      BufferedReader bufferedReader = new BufferedReader(fileReader);
      String line;
      int i = 0;
      int[] qtf = new int[vector.length];
      int[] dtf = new int[vector.length];
      while((line = bufferedReader.readLine())!=null) {
        String[] s;
        if(i == 0) {
          s = line.split(" ");
          boolean flag = false;
          for(String word: s) {
            if(flag == true) {
              //System.out.println("hi"+word.indexOf("\t"));
              totalWordsDoc = Integer.parseInt(word.substring(0,word.indexOf("\t")));
              break;
            }
            if(word.equals("Words:")) {
              flag = true;
            }
          }
          //System.out.println("totalWords:" +totalWordsDoc);
        }
        else {
          s = line.split(",");
          String curr = s[0].substring(s[0].indexOf("\t")+1);
          myMapTF.put(curr, s.length-2);
          //System.out.println(myMapTF.get(curr));
        }
        i++;
      }

      fileReader = new FileReader(f1);
      bufferedReader = new BufferedReader(fileReader);
      while((line = bufferedReader.readLine())!=null) {
        String[] s = line.split("\t");
        myMapIDF.put(s[0], Integer.parseInt(s[2]));
      }
      qTFIDF = new double[vector.length];
      dTFIDF = new double[vector.length];
      double TF = 0;
      double IDF = 0;
      i = 0;
      for(String word: vector) {
        TF = ((double)1/3)+(((double)2/3)*(myMapTF.get(word)/NUMDOCS));
        TF = TF/(1-TF);
        //System.out.print(TF + " ");
        //System.out.println(myMapTF.get(word));
        IDF = Math.log((NUMDOCS+0.5)/(myMapIDF.get(word)+0.5))/Math.log(2);
        //System.out.println(word +myMapIDF.get(word));
        //System.out.print(IDF + " ");
        dTFIDF[i] = TF*IDF;
        //System.out.println(word + " " +dTFIDF[i] );
        i++;
      }

    } catch(IOException e) {
      e.printStackTrace();
    } catch(InterruptedException ie) {
      ie.printStackTrace();
    }
    double sum = 0.0;
    for(double num: dTFIDF) {
      sum+=Math.log(num)/Math.log(2);
      //System.out.print(sum+" ");
    }
    return sum;
  }

  public static void parseXML(String filename) {
    try{
      PrintWriter output = new PrintWriter(new FileWriter("cacm.query.JSON"));

      File file = new File(filename);
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.parse(file);
      doc.getDocumentElement().normalize();
      
      output.write("{\n");
      output.write("\t\"queries\" : "+ "[\n");
      //output.write("\t\"" + doc.getDocumentElement().getNodeName() +"\": [\n");
      NodeList nList = doc.getElementsByTagName("query");

      for(int temp = 0; temp < nList.getLength(); temp++) {
        Node nNode = nList.item(temp);
                //System.out.println("\nCurren Element: " + nNode.getNodeName());
        if(nNode.getNodeType() == Node.ELEMENT_NODE) {
          Element eElement = (Element) nNode;
                    output.write("\t\t{\n");
          output.write("\t\t\t\"number\" : "+"\""+ eElement.getElementsByTagName("number").item(0).getTextContent()+"\",\n");
          output.write("\t\t\t\"text\" : "+"\""+eElement.getElementsByTagName("text").item(0).getTextContent()+"\",\n");
        } 
          output.write("\t\t},\n");
          //output.write("\t},\n");

      }
      output.write("\t]");
      output.write("}");
      
      output.close();
    } catch(Exception e) {
      e.printStackTrace();
    } 
  }

  public static void part3a() {
    parseXML("cacm.query.xml");
    try {
      ProcessBuilder process = new ProcessBuilder("galago", "batch-search", "--requested=100", "--index=./project1-index" ,"cacm.query.JSON");
      process.redirectOutput(new File("3a.txt"));
      process.redirectError(ProcessBuilder.Redirect.INHERIT);
      Process p = process.start();
      p.waitFor();
      
      ProcessBuilder process1 = new ProcessBuilder("/bin/sh" , "-c", "awk \'$4==1, $4==2 { print }\' 3a.txt");
      process1.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      Process p1 = process1.start();
      p1.waitFor();

    } catch(Exception e) {
      e.printStackTrace();
    }
  }

  public static String parseCACM(String og) {
    return og.substring(og.indexOf("CACM-"), og.indexOf(".html"));
  }

  public static LinkedHashMap<String, Double> sortByValue(HashMap<String, Double> myMap) {
    List<String> mapKeys = new ArrayList<>(myMap.keySet());
    List<Double> mapValues = new ArrayList<>(myMap.values());
    Collections.sort(mapValues);
    Collections.sort(mapKeys);
    LinkedHashMap<String,Double> sorted = new LinkedHashMap<>();

    Iterator<Double> valueIt = mapValues.iterator();
    while(valueIt.hasNext()) {
      Double val = valueIt.next();
      Iterator<String> keyIt = mapKeys.iterator();

      while(keyIt.hasNext()) {
        String key = keyIt.next();
        Double comp1 = myMap.get(key);
        Double comp2 = val;

        if(comp1 == comp2) {
          keyIt.remove();
          sorted.put(key,val);
          break;
        }
      }
    }
    return sorted;

  }

  public static void part3b(String q1, String q2) {
     try {
      q1 = "\'"+q1 +"\'";
      q2 = "\'"+q2+"\'";
      ProcessBuilder process = new ProcessBuilder("/bin/sh", "-c", "galago batch-search --requested=100 --index=./project1-index --query+"+q1+" --query+"+q2);
      File myF = new File("queries.txt");
      process.redirectOutput(myF);
      process.redirectError(ProcessBuilder.Redirect.INHERIT);
      Process p = process.start();
      p.waitFor();

      FileReader fileReader = new FileReader(myF);
      BufferedReader bufferedReader = new BufferedReader(fileReader);
      String line; int i = 0;
      HashMap<String, Double> myMapQ1 = new HashMap<String, Double>();
      HashMap<String, Double> myMapQ2 = new HashMap<String, Double>();
      HashMap<String, Double> myMap2Q1 = new HashMap<String, Double>();
      HashMap<String, Double> myMap2Q2 = new HashMap<String, Double>();

      while((line = bufferedReader.readLine())!=null) {
        String[] s = line.split(" ");
        if(i < 100) {
          myMapQ1.put(parseCACM(s[2]),0.0);
          myMap2Q1.put(parseCACM(s[2]),0.0);
        }
        else {
          myMapQ2.put(parseCACM(s[2]),0.0);
          myMap2Q2.put(parseCACM(s[2]),0.0);
        }
        i++;
      }
      i = 0;
      //String q1 = "\'set1 very high level languages\'";
      //String q2 = "\'distributed computing structures and algorithms\'";
      Iterator it = myMapQ1.entrySet().iterator();
      while(it.hasNext()) {
        System.out.print(i);i++;
        Map.Entry pair = (Map.Entry)it.next();
        String doc = pair.getKey().toString();
        int docNum = Integer.parseInt(doc.substring(doc.indexOf("-")+1));
        Double tfIDF = tfIDF(q1,docNum);
        Double RSV = RSV(q1, docNum); 
        if(tfIDF.isNaN()) {
          tfIDF = 0.0;
        }
        myMapQ1.put(doc, tfIDF);
        myMap2Q1.put(doc, RSV);
        //System.out.println(doc +"   "+ tfIDF + " " + RSV);
      }
      it = myMapQ2.entrySet().iterator();
      i = 0;
      while(it.hasNext()) {
        System.out.print(i);i++;
        Map.Entry pair = (Map.Entry)it.next();
        String doc = pair.getKey().toString();
        int docNum = Integer.parseInt(doc.substring(doc.indexOf("-")+1));
        Double tfIDF = tfIDF(q2,docNum);
        Double RSV = RSV(q2, docNum);
        if(tfIDF.isNaN()) {
          tfIDF = 0.0;
        }
        myMapQ2.put(doc, tfIDF);
        myMap2Q2.put(doc,RSV);
        //System.out.println(doc +"   "+ tfIDF);
      }
      System.out.println("------------------------------------------------------");

       
      PrintWriter pw = new PrintWriter(new FileWriter("res_cosine"));
      LinkedHashMap<String, Double> sortedq1 = sortByValue(myMapQ1);
      LinkedHashMap<String, Double> sorted2q1 = sortByValue(myMap2Q1);
      it = sortedq1.entrySet().iterator();
      i = 100;
      while(it.hasNext()) {
        i--;
        Map.Entry pair = (Map.Entry)it.next();
        pw.write("11 Q0 " +pair.getKey()+" " + i+ " "+ pair.getValue()+" galago\n");
      }
      i = 100; 
      LinkedHashMap<String, Double> sortedq2 = sortByValue(myMapQ2);
      LinkedHashMap<String, Double> sorted2q2 = sortByValue(myMap2Q2);
      it = sortedq2.entrySet().iterator();
      while(it.hasNext()) {
        i--;
        Map.Entry pair = (Map.Entry)it.next();
        pw.write("23 Q0 " + pair.getKey()+"  "+ i + " " + pair.getValue()+" galago\n");
      }
      pw.close();

      PrintWriter pw1 = new PrintWriter(new FileWriter("res_rsv"));
      it = sorted2q1.entrySet().iterator();
      i = 100;
      while(it.hasNext()) {
        i--;
        Map.Entry pair = (Map.Entry)it.next();
        pw1.write("11 Q0 " +pair.getKey()+" "+ i +" " + pair.getValue()+" galago\n");
      }
      it = sorted2q1.entrySet().iterator();
      i = 100;
      while(it.hasNext()) {
        i--;
        Map.Entry pair = (Map.Entry)it.next();
        pw1.write("23 Q0 " +pair.getKey()+" "+ i + " " + pair.getValue()+" galago\n");
      }pw1.close();
      ProcessBuilder gal = new ProcessBuilder("/bin/sh","-c" ,"galago eval --baseline=./res_cosine --judgments=./cacm.rel");
      gal.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      gal.redirectError(ProcessBuilder.Redirect.INHERIT);
      Process p1 = gal.start();
      p1.waitFor();
     
      ProcessBuilder gal0 = new ProcessBuilder("/bin/sh", "-c" ,"galago eval --baseline=./res_rsv --judgments=./cacm.rel");
      gal0.redirectOutput(ProcessBuilder.Redirect.INHERIT);
      gal0.redirectError(ProcessBuilder.Redirect.INHERIT);
      Process p2 = gal0.start();
      p2.waitFor();


    } catch(Exception e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {


    
    System.out.println("CHOOSE AN OPTION:");
    System.out.println("1. Part 1");
    System.out.println("2. Part 2A-C");
    System.out.println("3. Part 2DE");
    System.out.println("4. Part 2 Cos Similarity");
    System.out.println("5. Part 2 RSV");
    System.out.println("6. Part 3a");
    System.out.println("7. Part 3b");


    String corp_index="--index=./project1-index";
    System.out.print("INPUT: ");
    Scanner myS = new Scanner(System.in);
    int input = myS.nextInt();
    String query = "";
    int doc = 0;

    switch(input) {
      case 1:
        System.out.println("Input Query: ");
        query = myS.next();
        part1(corp_index, query);
        break;
      case 2:
        part2(corp_index);
        break;
      case 3:
        System.out.println("Input Query: ");
        query = myS.next();
        printTermFreq(query);
        break;
      case 4:
        query = myS.next();
        doc = myS.nextInt();
        System.out.println("tfIDF = " + tfIDF(query, doc));
        break;
      case 5:
        query = myS.next();
        doc = myS.nextInt();
        System.out.println("RSV = " + RSV(query, doc));
        break;
      case 6:
        part3a();
        System.out.println("ALL 100 in 3a.txt");
        break;
      case 7:
        System.out.println("Input Query1: ");
        query = myS.next();
        System.out.println("Input Query2: ");
        String query1 = myS.next();
        part3b(query, query1);
        break;
      default:
        break;
    }

    //part1(corp_index);
    //part2(corp_index);
    //printTermFreq("science");
    //System.out.println("tfIDF = " + tfIDF("optimization of intermediate and machine code", 5));
    //System.out.println(RSV("i am interested in hidden line and hidden surface algorithms for cylinders toroid spheres and cones this is a rather specialized topic in computer graphics",10));
    //parseXML("cacm.query.xml");
    //part3a();
    //part3b();
    System.out.println("DONE!");
  }
}
