/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author julian
 */
public class Ejercicio10Cliente {
    public static void main(String[] args) {
        try {
            Socket ej10Socket = null;
            PrintWriter out = null;
            BufferedReader in = null;
            ej10Socket = new Socket(args[0], 2090);
            out = new PrintWriter(ej10Socket.getOutputStream(), true);                      // Crea el buffer para enviar informacion al servidor.
            in = new BufferedReader(new InputStreamReader(ej10Socket.getInputStream()));    // Crea el buffer para recibir informacion del servidor.
            System.out.println("Ingrese el numero de la opción solicitada:\n" +
                                "\t1: Numero decimal a binario.\n" +
                                "\t2: Numero binario a hexadecimal.\n" +
                                "\t3: Peso a dolar.\n" +
                                "\t4: Peso a euro.\n" +
                                "\t5: Hora del servidor.\n" +
                                "\t6: Dia del servidor.\n" +
                                "\t7: Sumar numeros.\n" +
                                "\t8: Restar numeros.\n" +
                                "\t9: Multiplicar numeros.\n" +
                                "\t10: Dividir numeros.");
            BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
            String entrada;
            String fromServer;
            String toServer;
	    String salida;
            entrada = stdIn.readLine();
            int opcion;
            opcion = Integer.parseInt(entrada);
            switch (opcion) {
                case 1:{
                    System.out.println("Ingrese el numero:");
                    entrada = stdIn.readLine();
                    toServer = "decToBin-" + entrada;
		    long startTime = System.nanoTime();
                    out.println(toServer);
                    salida = in.readLine();
		    long estimatedTime = System.nanoTime() - startTime;
		    System.out.println("Su numero en binario es: " + salida);
		    System.out.println("Tiempo demorado: " + estimatedTime);

                } break;
                case 2:{
                    System.out.println("Ingrese el numero:");
                    entrada = stdIn.readLine();
                    toServer = "binToHex-" + entrada;
		    long startTime = System.nanoTime();
                    out.println(toServer);
                    salida = in.readLine();
		    long estimatedTime = System.nanoTime() - startTime;
                    System.out.println("Su numero en hexadecimal es: " + salida);
		    System.out.println("Tiempo demorado: " + estimatedTime);
                } break;
                case 3:{
                //Llamado al servidor para convertir de pesos a dolares.
                    System.out.println("Ingrese la cantidad de pesos:");
                    entrada = stdIn.readLine();
                    toServer = "PesoADolar-" + entrada;
		    long startTime = System.nanoTime();
                    out.println(toServer);
                    salida = in.readLine();
		    long estimatedTime = System.nanoTime() - startTime;
                    System.out.println("Representan " + salida + " dolares.");
		    System.out.println("Tiempo demorado: " + estimatedTime);
                } break;
                case 4:{
                    System.out.println("Ingrese la cantidad de pesos:");
                    entrada = stdIn.readLine();
                    toServer = "PesoAEuro-" + entrada;
		    long startTime = System.nanoTime();
                    out.println(toServer);
                    salida = in.readLine();
		    long estimatedTime = System.nanoTime() - startTime;
                    System.out.println("Representan " + salida + " euros.");
		    System.out.println("Tiempo demorado: " + estimatedTime);
                } break;
                case 5:{
                    toServer = "f_hora";
		    long startTime = System.nanoTime();
                    out.println(toServer);
                    salida = in.readLine();
		    long estimatedTime = System.nanoTime() - startTime;
                    System.out.println(salida);
		    System.out.println("Tiempo demorado: " + estimatedTime);
                } break;
                case 6:{
                    toServer = "f_dia";
		    long startTime = System.nanoTime();
                    out.println(toServer);
                    salida = in.readLine();
		    long estimatedTime = System.nanoTime() - startTime;
                    System.out.println(salida);
		    System.out.println("Tiempo demorado: " + estimatedTime);
                } break;
                case 7:{
                    System.out.println("Ingrese la cantidad numeros a sumar:");
                    entrada = stdIn.readLine();
                    int cantidad;
                    cantidad = Integer.parseInt(entrada);
                    if (cantidad<2 || cantidad>4){
                        System.out.println("Solo se puede sumar entre 2 y 4 números.");
                    } else {
                        for (int i=0;i<cantidad;i++){
                            System.out.println("Ingrese el numero");
                            entrada += "-" + stdIn.readLine();
                        }
		        long startTime = System.nanoTime();
                        out.println("suma-"+entrada);
                        salida = in.readLine();
		        long estimatedTime = System.nanoTime() - startTime;
                        System.out.println("El resultado es " + salida);
		        System.out.println("Tiempo demorado: " + estimatedTime);
                    }
                } break;
                case 8:{
                    System.out.println("Ingrese la cantidad numeros a restar:");
                    entrada = stdIn.readLine();
                    int cantidad;
                    cantidad = Integer.parseInt(entrada);
                    if (cantidad<2 || cantidad>4){
                        System.out.println("Solo se puede restar entre 2 y 4 números.");
                    } else {
                        for (int i=0;i<cantidad;i++){
                            System.out.println("Ingrese el numero");
                            entrada += "-" + stdIn.readLine();
                        }
		        long startTime = System.nanoTime();
                        out.println("resta-"+entrada);
                        salida = in.readLine();
		        long estimatedTime = System.nanoTime() - startTime;
                        System.out.println("El resultado es " + salida);
    		        System.out.println("Tiempo demorado: " + estimatedTime);
                    }
                } break;
                case 9:{
                    System.out.println("Ingrese el primer numero");
                    entrada = stdIn.readLine();
                    System.out.println("Ingrese el segundo numero");
                    entrada += "-" + stdIn.readLine();
		    long startTime = System.nanoTime();
                    out.println("multiplicacion-"+entrada);
                    salida = in.readLine();
		    long estimatedTime = System.nanoTime() - startTime;
                    System.out.println("El resultado es " + salida);
		    System.out.println("Tiempo demorado: " + estimatedTime);                    
                } break;
                case 10:{
                    System.out.println("Ingrese el dividendo");
                    entrada = stdIn.readLine();
                    System.out.println("Ingrese el divisor");
                    float divisor = Float.parseFloat(stdIn.readLine());
                    if (divisor == 0) {
                        System.out.println("No se puede dividir por 0.");
                        break;
                    } else {
                        entrada += "-" + divisor;
		        long startTime = System.nanoTime();
                        out.println("division-"+entrada);
                        salida = in.readLine();
		        long estimatedTime = System.nanoTime() - startTime;
                        System.out.println("El resultado es " + salida);    
		        System.out.println("Tiempo demorado: " + estimatedTime);
                    }
                } break;
                default :{
                    System.out.println("Opcion no valida.");
                }
            }
            out.close();
            in.close();
            stdIn.close();
            ej10Socket.close();
        
        } catch (IOException ex) {
            Logger.getLogger(Ejercicio10Cliente.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}

