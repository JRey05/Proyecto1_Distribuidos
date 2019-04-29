/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.LocalDateTime;

/**
 *
 * @author julian
 */
public class Ejercicio10Servidor {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        int puerto;
        ServerSocket serverSocket = null;
        puerto = 2090;
        try {
            serverSocket = new ServerSocket(2090);
	    System.out.println("estoy despu�s de crear el socket");
        } catch (IOException e) {
            System.err.println("Could not listen on port: 2090.");
            System.exit(1);
        }

        Socket clientSocket = null;
        while(true){
            try {
                clientSocket = serverSocket.accept();
            } catch (IOException e) {
                System.err.println("Accept failed.");
                System.exit(1);
            }
            Thread t = new Ejercicio10HiloServidor(clientSocket);
            t.run();

        }
    }
}
