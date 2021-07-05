public class zad3 {
    public enum Pierwiastki {
        H("wodór", 1, 1.00794),
        He("hel", 2, 4.002602),
        Li("lit", 3, 6.941),
        Be("beryl", 4, 9.012182),
        B("bor", 5, 10.806),
        C("węgiel", 6, 12.010),
        N("azot", 7, 14.00643),
        O("tlen", 8, 15.999),
        F("fluor", 9, 18.9984032),
        Ne("neon", 10, 20.1797),
        Na("sód", 11, 22.989769),
        Mg("magnez", 12, 24.305),
        Al("glin", 13, 26.981539),
        Si("krzem", 14, 28.0855),
        P("fosfor", 15, 30.973762),
        S("siarka", 16, 32.066),
        Cl("chlor", 17, 35.4527),
        Ar("argon", 18, 39.948);

        String nazwa;
        int liczba_atomowa;
        double masa_atomowa;

        private Pierwiastki(String nazwa, int liczba_atomowa, double masa_atomowa) {
            this.nazwa = nazwa;
            this.liczba_atomowa = liczba_atomowa;
            this.masa_atomowa = masa_atomowa;
        }

        public String toString() {
            return super.toString() + " " + nazwa + " " + liczba_atomowa + " " + masa_atomowa;
        }

    }
    public static void main(String args[]) {
        for (Pierwiastki p: Pierwiastki.values()) {
            System.out.println(p);
        }

    }
}
