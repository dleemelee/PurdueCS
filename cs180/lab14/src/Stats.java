import java.nio.BufferUnderflowException;
import java.util.HashMap;
import java.util.Map;
import java.io.*;
/**
 * Created by lee2173 on 12/3/15.
 */
public class Stats {
    public static Map<String, Integer> wins(Map<String,Integer> map, String s){
        int score1 = 0;
        int score2 = 0;
        String[] arr = s.split(" ");
        String team1 = "";
        String team2 = "";
        boolean vsCheck = false;
        for(int i = 1; i < arr.length; i++) {
            if(arr[i].equals("vs.")) {
                vsCheck = true;
            }
            else if(!vsCheck){
                if(map.containsKey(arr[i])) {
                    if(arr[0].equals("0")){
                        map.put(arr[i], map.get(arr[i]) + 1);
                    }
                    else{
                        map.put(arr[i], map.get(arr[i]));
                    }
                }
                else{
                    if(arr[0].equals("0")){
                        map.put(arr[i], 1);
                    }
                    else{
                        map.put(arr[i], 0);
                    }
                }
            }
            else{
                if(map.containsKey(arr[i])) {
                    if(arr[0].equals("0")){
                        map.put(arr[i], map.get(arr[i]));
                    }
                    else{
                        map.put(arr[i], map.get(arr[i])+1);
                    }
                }
                else{
                    if(arr[0].equals("0")){
                        map.put(arr[i], 0);
                    }
                    else{
                        map.put(arr[i], 1);
                    }
                }
            }
        }
        return map;
    }

    public static String winner(Map<String,Integer> map) {
        int maxValue = 0;
        String winningTeam = "";

        for (Map.Entry<String, Integer> entry : map.entrySet())
        {
            if( maxValue < entry.getValue() ) {
                maxValue = entry.getValue();
                winningTeam = entry.getKey();
            }

        }
        return winningTeam;
    }

    public static void main(String[] args) {
        File f = new File("/homes/lee2173/cs180/lab14/test_inputs.txt");
        Map<String, Integer> myMap = new HashMap<String, Integer>();
        FileReader fr;
        BufferedReader br;
        try{
            fr = new FileReader(f);
            br = new BufferedReader(fr);
            for (String x = br.readLine(); x != null; x=br.readLine() ){
                wins(myMap, x);
            }
        }catch (FileNotFoundException e) {
            e.printStackTrace();
        }catch (IOException e) {
            e.printStackTrace();
        }
//        for (Map.Entry<String, Integer> entry : myMap.entrySet()) {
//            String key = entry.getKey().toString();;
//            Integer value = entry.getValue();
//            System.out.println("key, " + key + " value " + value );
//        }
        System.out.println(winner(myMap));

    }
}
