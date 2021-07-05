class Jawna
  @napis = ""

  def to_s()
    @napis
  end

  def put(napis)
    @napis = napis
  end

  def zaszyfruj (klucz)
    result =[]
    tmp_napis = @napis.split('')

    for i in tmp_napis
      result << klucz[i]
    end

    res = Zaszyfrowane.new()
    res.put(result.join(''))
    return res
  end

end


class Zaszyfrowane
  @napis = ""

  def to_s()
    @napis
  end

  def put(napis)
    @napis = napis
  end

  def odszyfruj (klucz)
    klucz = klucz.invert()
    result =[]
    tmp_napis = @napis.split('')

    for i in tmp_napis
      result << klucz[i]
    end

    res = Jawna.new()
    res.put(result.join(''))
    return res

  end

end
#====================porgram do testu =================================
klucz = {
        'a' => 'x',
        'b' => 'y',
        'c' => 'z',
        'd' => 'f',
        'e' => 'a',
        'f' => 'b',
        'g' => 'c',
        'h' => 'd',
        'i' => 'e',
        'j' => 'f',
        'k' => 'g',
        'l' => 'h',
        'm' => 'i',
        'n' => 'j',

        }
#INICJALIZACJA
j = Jawna.new()
j.put("abcdefghijklmn")

#WYPISANIE
puts(j.to_s())

#SZYFROWANIE
z = j.zaszyfruj(klucz)

#WYPISANIE
puts(z.to_s())

#ODSZYFROWYWANIE
j = z.odszyfruj(klucz)

#WYPISANIE
puts(j.to_s())


#==============================
#INICJALIZACJA
j = Jawna.new()
j.put("aaaa")

#WYPISANIE
puts(j.to_s())

#SZYFROWANIE
z = j.zaszyfruj(klucz)

#WYPISANIE
puts(z.to_s())

#ODSZYFROWYWANIE
j = z.odszyfruj(klucz)

#WYPISANIE
puts(j.to_s())


#===============================
#INICJALIZACJA
z = Zaszyfrowane.new()
z.put("xyzabcd")

#WYPISANIE
puts(z.to_s())

#ODSZYFROWANIE
j = z.odszyfruj(klucz)

#WYPISANIE
puts(j.to_s())

#SZYFROWYWANIE
z = j.zaszyfruj(klucz)

#WYPISANIE
puts(z.to_s())