(require 'dash)
(require 'json)

(defun atreus-key (key)
  (pcase key
    (`("reset") "300") ("FN" "301")
    (`("shift" ,keycode) (format "100 + KEY_%s" keycode))
    ("CTRL" "101") ("ALT" "104") ("GUI" "102") ("SHIFT" "108")
    (keycode (format "KEY_%s" keycode))))

(defun atreus-dead-key (row)
  (append (-take 5 row) '("0") (-drop 5 row)))

(defun atreus-insert-layer (layer)
  (let ((layer-name (car layer))
        (rows (cdr layer)))
    (insert "int " (symbol-name layer-name) "[" "44" "] = {")
    (dolist (row (list (atreus-dead-key (nth 0 rows))
                       (atreus-dead-key (nth 1 rows))
                       (nth 2 rows) (nth 3 rows)))
      (insert "\n    ")
      (dolist (key row)
        (insert (atreus-key key) ", ")))
    (delete-region (- (point) 2) (- (point) 1))
    (insert "};\n\n")))

(defun atreus-insert ()
  (interactive)
  (let* ((json-array-type 'list)
         (f (if ido-mode
                (ido-read-file-name "Layout json file: ")
              (read-file-name "Layout json file: ")))
         (layout (json-read-file f)))
    (mapc 'atreus-insert-layer layout)))

;; TODO: insert into the proper command, wire into make
;; TODO: emit HTML output of layout

(provide 'atreus)
