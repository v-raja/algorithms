(defn remove-item [xs n]
  (concat (subvec xs 0 n) (subvec xs (inc n)))
)

(defn qsort [xs]
  (defn partition-recur [ys p ls rs]
    (if (empty? ys)
      (into [] (concat (conj (qsort ls) p) (qsort rs)))
      (if (> p (first ys))
          (recur (rest ys) p (conj ls (first ys)) rs)
          (recur (rest ys) p ls (conj rs (first ys)))
      )
    )
  )
  (if (empty? xs)
    xs
    (let [p_idx (rand-int (count xs))
          p     (nth xs p_idx)
          ys    (remove-item xs p_idx)]
      (partition-recur ys p [] [])
    )
  )

)

