func fraction (int int)
| _ 0 = none
| n d = { 
  n = n
  d = d
}

operator + (fraction fraction)
| none none = none
| a    none = none
| none b    = none
| a    b    = 
  let base = a.d * b.d
  in
    fraction (base * (a.n + b.n)) base