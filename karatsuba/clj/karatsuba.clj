(defn square [x]
  (* x x)
)

(defn expt [x n]
  "returns x to the power of n"
  (let [x (bigint x)
        n (bigint n)]
  (cond (zero? n) 1
        (even? n) (square (expt x (/ n 2)))
        :else (* x (expt x (dec n)))
  ))
)

(defn len [x]
  "returns the number of digits of x"
  (let [num_digit
        (fn [x count]
          (if (= (quot x (expt 10 count)) 0)
            count
            (recur x (inc count))
          )
        )]
    (num_digit x 1)
  )
)

(defn split_at [x m]
  "returns a list y where (second y) is
    the last m digits of x and
    (first y) is the remaining digits"
  (let [divisor (expt 10 m)]
    [(quot x divisor) (rem  x divisor)]
  )
)

(defn karatsuba [x y]
  "multiplies x and y using the Karatsuba algorithm"
  (let [len_x (len x)
        len_y (len y)]
    (if (or (= len_x 1) (= len_y 1))
      (* x y)
      (let [half_len_x   (quot (+ 1 len_x) 2)
            half_len_y   (quot (+ 1 len_y) 2)
            max_half_len (max half_len_x half_len_y)
            [a, b]       (split_at x max_half_len)
            [c, d]       (split_at y max_half_len)
            ac           (karatsuba a c)
            bd           (karatsuba b d)
            ad_plus_bc   (- (karatsuba (+ a b) (+ c d)) ac bd)]
        (+ (* ac (expt 10 (* 2 max_half_len)))
           (* ad_plus_bc (expt 10 max_half_len))
           bd)
      )
    )
  )
)


(defn test_karatsuba [file]
  (for [test_case_str (clojure.string/split-lines (slurp file))]
    (let [test   (map read-string (clojure.string/split test_case_str #" "))
          x      (first test)
          y      (second test)
          actual (* (bigint x) (bigint y))
          res    (karatsuba x y)]
      (if (not= res actual)
        (println (format "Test Failed: %d x %d = %d, actual: %d" x y res actual))
      )
    )
  )
)
