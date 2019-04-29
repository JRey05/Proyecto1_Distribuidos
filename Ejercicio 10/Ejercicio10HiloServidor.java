/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.time.LocalDateTime;

/**
 *
 * @author julian
 */
public class Ejercicio10HiloServidor extends Thread {
    private Socket socket = null;

    public Ejercicio10HiloServidor(Socket socket) {
	super("Ejercicio10HiloServidor");
	this.socket = socket;
    }

    public void run() {
        try{
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);    //Crea el buffer para envia las respuestas.
            BufferedReader in = new BufferedReader(
                                	new InputStreamReader(
                        		socket.getInputStream()));                //Crea el buffer para recibir las consultas.
            String inputLine, outputLine;
            while ((inputLine = in.readLine()) != null) {
                String parametros[] = inputLine.split("-");
                switch (parametros[0]) {
                    case "decToBin":{
                        int numero = Integer.parseInt(parametros[1],10);
                        out.println(Integer.toString(numero,2));
                    }break;
                    case "binToHex":{
                        int numero = Integer.parseInt(parametros[1],2);
                        out.println(Integer.toString(numero,16));
                    }break;
                    case "PesoADolar":{
                        float dolares;
                        dolares = Float.parseFloat(parametros[1]);
                        dolares *= 0.022;
                        out.println(dolares);
                    } break;
                    case "PesoAEuro":{
                        float dolares;
                        dolares = Float.parseFloat(parametros[1]);
                        dolares *= 0.02;
                        out.println(dolares);
                    } break;
                    case "f_hora": {
                        LocalDateTime locaDate = LocalDateTime.now();
                        int hours  = locaDate.getHour();
                        int minutes = locaDate.getMinute();
                        int seconds = locaDate.getSecond();
                        out.println("Hora actual : " + hours  + ":"+ minutes +":"+seconds); 
                    }break;
                    case "f_dia": {
                        LocalDateTime locaDate = LocalDateTime.now();
                        int dia = locaDate.getDayOfMonth();
                        int mes = locaDate.getMonthValue();
                        int anho = locaDate.getYear();
                        out.println("Fecha actual : " + dia  + "/"+ mes +"/"+anho); 

                    }break;
                    case "suma": {
                        float resultado = 0;
                        for(int i=0; i<Integer.parseInt(parametros[1]);i++) {
                            resultado+=Float.parseFloat(parametros[i+2]);
                        }
                        out.println(resultado);
                    }break;
                    case "resta": {
                        float resultado = Float.parseFloat(parametros[2]);
                        for(int i=0; i<Integer.parseInt(parametros[1])-1;i++) {
                            resultado-=Float.parseFloat(parametros[i+3]);
                        }
                        out.println(resultado);
                    }break;
                    case "multiplicacion": {
                        float resultado = Float.parseFloat(parametros[1]) * Float.parseFloat(parametros[2]);
                        out.println(resultado);
                    }break;
                    case "division": {
                        float resultado = Float.parseFloat(parametros[1]) / Float.parseFloat(parametros[2]);
                        out.println(resultado);
                    }
                }
                out.close();
                in.close();
                socket.close();
            }
        } catch(Exception e){
        }
    }
}
