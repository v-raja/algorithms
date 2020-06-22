(defn merge_and_count_split_inv[x y]
  "key idea: assume x and y are sorted"
  (let [merge_and_count_recur (fn [x y merged cnt]
    (if (or (empty? x) (empty? y))
      [(into [] (concat merged x y)) cnt]
      (if (< (first y) (first x))
        (recur x (rest y) (conj merged (first y)) (+ cnt (count x)))
        (recur (rest x) y (conj merged (first x)) cnt)
      )
    ))]
    (merge_and_count_recur x y [] 0)
  )
)

(defn sort_and_count_inv [array]
  (if (= (count array) 1)
    [array 0]
    (let [half_len                           (quot (count array) 2)
          left_half                          (take half_len array)
          right_half                         (drop half_len array)
          [left_half_sorted  left_inv_cnt]   (sort_and_count_inv left_half)
          [right_half_sorted right_inv_cnt]  (sort_and_count_inv right_half)
          [array_sorted split_inv_cnt]       (merge_and_count_split_inv left_half_sorted right_half_sorted)]
      [array_sorted (+ left_inv_cnt right_inv_cnt split_inv_cnt)]
    )
  )
)


(defn count_inversions [file]
  (print (sort_and_count_inv (map read-string (clojure.string/split (slurp file) #"\n"))))
  ; (for [test_case_str (clojure.string/split-lines (slurp file))]
  ;   (let [test   (map read-string (clojure.string/split test_case_str #" "))
  ;         x      (first test)
  ;         y      (second test)
  ;         actual (* (bigint x) (bigint y))
  ;         res    (karatsuba x y)]
  ;     (if (not= res actual)
  ;       (println (format "Test Failed: %d x %d = %d, actual: %d" x y res actual))
  ;     )
  ;   )
  ; )
)
