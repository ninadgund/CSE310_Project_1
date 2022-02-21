
preprocess <inputs/1.txt >inputs/1_pre-file.txt
preprocess <inputs/2.txt >inputs/2_pre-file.txt
preprocess <inputs/3.txt >inputs/3_pre-file.txt
preprocess <inputs/4.txt >inputs/4_pre-file.txt
preprocess <inputs/5.txt >inputs/5_pre-file.txt

experimentation inputs/1_pre-file.txt insertion <inputs/1.txt >inputs/1enc_expout.txt
experimentation inputs/2_pre-file.txt insertion <inputs/2.txt >inputs/2enc_expout.txt
experimentation inputs/3_pre-file.txt insertion <inputs/3.txt >inputs/3enc_expout.txt
experimentation inputs/4_pre-file.txt insertion <inputs/4.txt >inputs/4enc_expout.txt
experimentation inputs/5_pre-file.txt insertion <inputs/5.txt >inputs/5enc_expout.txt

experimentation inputs/1_pre-file.txt insertion <inputs/1.txt >>inputs/enc_expout.txt
experimentation inputs/2_pre-file.txt insertion <inputs/2.txt >>inputs/enc_expout.txt
experimentation inputs/3_pre-file.txt insertion <inputs/3.txt >>inputs/enc_expout.txt
experimentation inputs/4_pre-file.txt insertion <inputs/4.txt >>inputs/enc_expout.txt
experimentation inputs/5_pre-file.txt insertion <inputs/5.txt >>inputs/enc_expout.txt
