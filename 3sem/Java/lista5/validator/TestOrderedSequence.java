package validator;
import structures.*;

import java.util.Calendar;
import java.util.Iterator;

public class TestOrderedSequence {
    public TestOrderedSequence() {
        OrderedList<Integer> list = new OrderedList<Integer>();
        System.out.println("Wkładanie w różnej kolejności elementów:\n1,2,3,-20,0,5,4");
        list.insert(1);
        list.insert(2);
        list.insert(3);
        list.insert(-20);
        list.insert(0);
        list.insert(5);
        list.insert(4);
        System.out.println(list.toString());
        System.out.println("Usunięcie elementów:\n2,4,-20,5");
        list.remove(2);
        list.remove(4);
        list.remove(-20);
        list.remove(5);
        System.out.println(list.toString());
        System.out.println("Usunięcie elementów:\n1,0,3");
        list.remove(1);
        list.remove(0);
        list.remove(3);
        System.out.println(list.toString());
        System.out.println("Przywrocenie listy poczatkowej");
        list.insert(1);
        list.insert(2);
        list.insert(3);
        list.insert(-20);
        list.insert(0);
        list.insert(5);
        list.insert(4);
        System.out.println(list.toString());
        try {
            System.out.println("Minimalny element: " + String.valueOf(list.min()) );
            System.out.println("Maksymalny element: " + String.valueOf(list.max()) );
        }
        catch(IllegalAccessException e) {
            System.out.println(e.getMessage());
        }
        try {
            System.out.println("Na pozycji 3 jest: " + String.valueOf(list.at(3)));
            System.out.println("Na pozycji 0 jest: " + String.valueOf(list.at(0)));
            System.out.println("Na pozycji 7 jest (nie ma takiej poz.): ");
            System.out.println(String.valueOf(list.at(7)));
        }
        catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
        System.out.println("Czy element -20 znajduje sie na liscie?:\n" + String.valueOf(list.search(-20)));
        System.out.println("Czy element 51 znajduje sie na liscie?:\n" + String.valueOf(list.search(51)));
        try {
            System.out.println("-20 jest na pozycji: " + String.valueOf(list.index(-20)));
            System.out.println("5 jest na pozycji: " + String.valueOf(list.index(5)));
            System.out.println("100 jest na pozycji (nie ma takiego elem.): ");
            System.out.println(String.valueOf(list.index(100)));
        }
        catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }

        Iterator<Integer> it = list.iterator();
        System.out.println("\nDziałanie Iteratora:\n");
        System.out.println(list.toString());
        System.out.println(it.next() + " -> iterator.next()");
        System.out.println(it.next() + " -> iterator.next()");
        it.remove();
        System.out.println("Lista po usunieciu elementu po dwoch it.next() - czyli el. na 2 poz.");
        System.out.println(list.toString());
        for (Integer x : list) {
            System.out.println(x);
            
        }

        System.out.println("\n=================\n");
        OrderedList<String> list_string = new OrderedList<String>();
        System.out.println("Wkładanie w różnej kolejności elementów:");
        list_string.insert("aaa");
        list_string.insert("bbb");
        list_string.insert("ccc");
        System.out.println(list_string.toString());
        System.out.println("Usunięcie elementów:");
        list_string.remove("aaa");  
        System.out.println(list_string.toString());
        System.out.println("Usunięcie elementów:");
        list_string.remove("ccc");
        list_string.remove("bbb");
        System.out.println(list_string.toString());
        System.out.println("Przywrocenie listy poczatkowej");
        list_string.insert("aaa");
        list_string.insert("bbb");
        list_string.insert("ccc");
        System.out.println(list_string.toString());
        try {
            System.out.println("Minimalny element: " + String.valueOf(list_string.min()) );
            System.out.println("Maksymalny element: " + String.valueOf(list_string.max()) );
        }
        catch(IllegalAccessException e) {
            System.out.println(e.getMessage());
        }
        try {
            System.out.println("Na pozycji 0 jest: " + String.valueOf(list_string.at(0)));
            System.out.println("Na pozycji 2 jest: " + String.valueOf(list_string.at(2)));
            System.out.println("Na pozycji 3 jest (nie ma takiej poz.): ");
            System.out.println(String.valueOf(list_string.at(3)));
        }
        catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
        System.out.println("Czy element aaa znajduje sie na liscie?:\n" + String.valueOf(list_string.search("aaa")));
        System.out.println("Czy element kkk znajduje sie na liscie?:\n" + String.valueOf(list_string.search("kkk")));
        try {
            System.out.println("aaa jest na pozycji: " + String.valueOf(list_string.index("aaa")));
            System.out.println("ccc jest na pozycji: " + String.valueOf(list_string.index("ccc")));
            System.out.println("www jest na pozycji (nie ma takiego elem.): ");
            System.out.println(String.valueOf(list_string.index("www")));
        }
        catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }

        Iterator<String> it_string = list_string.iterator();
        System.out.println("\nDziałanie Iteratora:\n");
        System.out.println(list_string.toString());
        System.out.println(it_string.next() + " -> iterator.next()");
        System.out.println(it_string.next() + " -> iterator.next()");
        it_string.remove();
        System.out.println("Lista po usunieciu elementu po dwoch it.next() - czyli el. na 2 poz.");
        System.out.println(list_string.toString());
        for (String x : list_string) {
            System.out.println(x);
            
        }

        System.out.println("\n=================\n");
        OrderedList<Calendar> list_calendar = new OrderedList<Calendar>();
        System.out.println("Wkładanie w różnej kolejności elementów:");
        Calendar a = Calendar.getInstance();
        Calendar b = Calendar.getInstance();
        Calendar c = Calendar.getInstance();
        a.set(Calendar.HOUR, 3);
        b.set(Calendar.HOUR, 4);
        c.set(Calendar.HOUR, 5);
        System.out.println(String.valueOf(b.getTime()));
        System.out.println(String.valueOf(a.getTime()));
        System.out.println(String.valueOf(c.getTime()));
        list_calendar.insert(b);
        list_calendar.insert(a);
        list_calendar.insert(c);
        System.out.println();
        for (Calendar x : list_calendar) {
            System.out.println(x.getTime());   
        }
        System.out.println("Usunięcie elementów:");
        list_calendar.remove(a);  
        for (Calendar x : list_calendar) {
            System.out.println(x.getTime());   
        }
        System.out.println("Usunięcie elementów:");
        list_calendar.remove(c);
        list_calendar.remove(b);
        System.out.println(list_calendar.toString());
        System.out.println("Przywrocenie listy poczatkowej");
        list_calendar.insert(a);
        list_calendar.insert(b);
        list_calendar.insert(c);

        for (Calendar x : list_calendar) {
            System.out.println(x.getTime());   
        }
        try {
            System.out.println("Minimalny element: " + String.valueOf(list_calendar.min().getTime()) );
            System.out.println("Maksymalny element: " + String.valueOf(list_calendar.max().getTime()) );
        }
        catch(IllegalAccessException e) {
            System.out.println(e.getMessage());
        }
        try {
            System.out.println("Na pozycji 0 jest: " + String.valueOf(list_calendar.at(0).getTime()));
            System.out.println("Na pozycji 2 jest: " + String.valueOf(list_calendar.at(2).getTime()));
            System.out.println("Na pozycji 3 jest (nie ma takiej poz.): ");
            System.out.println(String.valueOf(list_calendar.at(3)));
        }
        catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
        System.out.println("Czy element a znajduje sie na liscie?:\n" + String.valueOf(list_calendar.search(a)));
        System.out.println("Czy element aktualny_czas znajduje sie na liscie?:\n" + String.valueOf(list_calendar.search(Calendar.getInstance())));
        try {
            System.out.println("a jest na pozycji: " + String.valueOf(list_calendar.index(a)));
            System.out.println("c jest na pozycji: " + String.valueOf(list_calendar.index(c)));
            System.out.println("aktualny_czas jest na pozycji (nie ma takiego elem.): ");
            System.out.println(String.valueOf(list_calendar.index(Calendar.getInstance())));
        }
        catch(IllegalArgumentException e){
            System.out.println(e.getMessage());
        }

        Iterator<Calendar> it_calendar = list_calendar.iterator();
        System.out.println("\nDziałanie Iteratora:\n");
        System.out.println(it_calendar.next().getTime() + " -> iterator.next()");
        System.out.println(it_calendar.next().getTime() + " -> iterator.next()");
        it_calendar.remove();
        System.out.println("Lista po usunieciu elementu po dwoch it.next() - czyli el. na 2 poz.");
        for (Calendar x : list_calendar) {
            System.out.println(x.getTime());
            
        }

    }
    
}
