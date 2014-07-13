;;; atreus.el --- for generating keyboard layouts

;; Copyright © 2014 Phil Hagelberg
;;
;; Author: Phil Hagelberg
;; URL: http://github.com/technomancy/atreus-firmware
;; Version: 0.1
;; Created: 2014-05-07
;; Package-Requires: ((json "1.2") (dash "2.3.0"))

;; This file is not part of GNU Emacs.

;;; Commentary:

;;; License:

;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License
;; as published by the Free Software Foundation; either version 3
;; of the License, or (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GNU Emacs; see the file COPYING.  If not, write to the
;; Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
;; Boston, MA 02110-1301, USA.

;;; Code:

(when (< emacs-major-version 24)
  (error "Requires Emacs 24."))

(require 'dash)
(require 'json)
(require 'org-table)

(defun atreus-filename ()
  (list (if ido-mode
            (ido-read-file-name "Layout json: ")
          (read-file-name "Layout json: "))))

(defun atreus-key (key)
  (pcase key
    (`("reset") "FUNCTION(0)") ("FN" "PRE_FUNCTION(1)")
    (`("pre-function" ,f) (format "PRE_FUNCTION(%s)" f))
    (`("function" ,f) (format "FUNCTION(%s)" f))
    (`("ctrl" ,keycode) (format "CTRL(KEY_%s)" keycode))
    (`("shift" ,keycode) (format "SHIFT(KEY_%s)" keycode))
    (`("alt" ,keycode) (format "ALT(KEY_%s)" keycode))
    (`("gui" ,keycode) (format "GUI(KEY_%s)" keycode))
    ("CTRL" "KEYBOARD_LEFT_CTRL")
    ("SHIFT" "KEYBOARD_LEFT_SHIFT")
    ("ALT"   "KEYBOARD_LEFT_ALT")
    ("GUI"   "KEYBOARD_LEFT_GUI")
    (`("layer" ,layer) (format "LAYER(%s)" layer))
    ("" "0") ; dead key
    (keycode (format "KEY_%s" keycode))))

(defun atreus-splice-row (row dead)
  (append (-take 5 row) dead (last row 5)))

(defun atreus-rows-add-dead (rows dead)
  (list (atreus-splice-row (nth 0 rows) dead)
        (atreus-splice-row (nth 1 rows) dead)
        (nth 2 rows) (nth 3 rows)))

(defun atreus-insert-layer (rows layer-name)
  (insert "int " layer-name "[" "44" "] = {")
  (dolist (row (atreus-rows-add-dead rows '("0")))
    (insert "\n    ")
    (dolist (key row)
      (insert (atreus-key key) ", ")))
  (delete-region (- (point) 2) (- (point) 1))
  (insert "};\n\n"))

(defun atreus-insert (layout-file)
  (let* ((json-array-type 'list)
         (layout (json-read-file layout-file))
         (layer-names (--map-indexed (format "layer%s" it-index) layout)))
    (setq zz (-zip layout layer-names))
    (dolist (named-layer (-zip layout layer-names))
      (atreus-insert-layer (car named-layer) (cdr named-layer)))
    (insert "int *layers[] = {")
    (insert (mapconcat 'identity layer-names ", "))
    (insert "};\n\n")
    (insert "#include \"layout_common.h\"\n")))

(defun atreus-make-layout (layout-file)
  "Compile Atreus firmware source from a given JSON layout descriptor."
  (interactive (atreus-filename))
  (save-window-excursion
    (find-file "layout.h")
    (delete-region (point-min) (point-max))
    (atreus-insert layout-file)
    (save-buffer)))

(defun atreus-make (layout-file)
  "Compile Atreus firmware binary from a given JSON layout descriptor.

With the prefix arg, uploads firmware to keyboard."
  (interactive (atreus-filename))
  (atreus-make-layout layout-file)
  (compile (if current-prefix-arg
               "make upload"
             "make")))

(defun atreus-key-html (key)
  (replace-regexp-in-string "_" " "
                            (if (listp key)
                                (concat (car key) "+" (cadr key))
                              key)))

(defun atreus-splice-layer (rows dead)
  (let ((middles (list (nth 5 (nth 2 rows))
                       (nth 5 (nth 3 rows)))))
    (list (atreus-splice-row (nth 0 rows) dead)
          (atreus-splice-row (nth 1 rows) dead)
          (atreus-splice-row (nth 2 rows) dead)
          (atreus-splice-row (nth 3 rows) middles))))

(defun atreus-html-layer (layer)
  (let ((rows (atreus-splice-layer layer '(" " " "))))
    (mapcar (apply-partially 'mapcar 'atreus-key-html) rows)))

(defun atreus-insert-html (layout-file)
  (let* ((json-array-type 'list)
         (layout (json-read-file layout-file))
         (layout-name (file-name-base layout-file))
         (layers (-interpose '(hline) (-map 'atreus-html-layer ll)))
         (org-export-highlight-first-table-line nil))
    (insert "<h2>" layout-name "</h2>\n\n")
            (insert (orgtbl-to-html (apply 'append layers) nil))
    (insert "\n\n")))

(defun atreus-view (layout-file)
  "View the HTML for a given JSON layout in the browser."
  (interactive (atreus-filename))
  (save-window-excursion
    (find-file "layout.html")
    (delete-region (point-min) (point-max))
    (atreus-insert-html layout-file)
    (save-buffer)
    (browse-url-of-file)))

(provide 'atreus) ;; atreus.el ends here
