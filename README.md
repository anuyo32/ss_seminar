## 使い方

1. このリポジトリをクローンしたいディレクトリに移動
```bash
$ cd hogehoge
```

2. このリポジトリをクローンする
```bash
$ git clone https://github.com/anuyo32/ss_seminar
```

3. クローンしたリポジトリに移動
```bash
$ cd ss_seminar
```

4. ビルド
```bash
$ make
```

5. 実行
```bash
$ ./bin/main
```

## makeの使い方

- コンパイルで生成されたオブジェクトファイル(.o)と依存関係ファイル(.d)を削除
```bash
$ make clean
```

- 上記ファイルに加え、実行ファイルも削除
```bash
$ make fclean
```

- ビルドのやり直し
```bash
$ make re
```

- dry-run(動作確認)：オプションで-nをつければOK
```bash
$ make -n clean
```
