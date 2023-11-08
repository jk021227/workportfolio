Dependencies:
- typing
- nltk
- fastprogress

Features selected:
    - POS tag
    - whether capitalized
    - previous BIO tag
    - previous word
    - previous POS tagger
    - previous previous word
    - previous previous POS tag
    - next word
    - next POS tag
    - next next word
    - next next POS tag

Score on the development set:
    31641 out of 32852 tags correct
    accuracy: 96.31
    8377 groups in key
    8592 groups in response
    7713 correct groups
    precision: 89.77
    recall:    92.07
    F1:         9.09 = 90.9
    rounded to: 9