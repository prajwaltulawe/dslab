import java.rmi.*;
public class AddClient {
    public static void main(String args[]) {
        try {
            // Get reference to the remote object

            String addServerURL = "rmi://" + args[0] + "/AddServer";
            AddServerIntf addServerIntf = (AddServerIntf) Naming.lookup(addServerURL);

            System.out.println("The first number is: " + args[1]);
            double d1 = Double.parseDouble(args[1]);

            System.out.println("The second number is: " + args[2]);
            double d2 = Double.parseDouble(args[2]);

            // Invoke remote method to add numbers
            System.out.println("The sum is: " + addServerIntf.add(d1, d2));

        } catch (Exception e) {
            System.out.println("Exception: " + e);
        }
    }
}

/*
Terminal 1:
javac *.java
rmic AddServerImpl

Terminal 2:
rmiregistry

Terminal 3:
java AddServer

Terminal 4:
java AddClient 127.0.0.1 5 8
or
java AddClient localhost:500 5 8
*/