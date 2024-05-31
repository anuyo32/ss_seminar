## 使い方

1. このリポジトリをクローンしたいディレクトリに移動
```bash
$ cd hogehoge
```

2. このリポジトリをクローンする
```bash
$ git clone https://github.com/maczac150/waseda_lab
```

3. クローンしたリポジトリに移動
```bash
$ cd waseda_lab
```

4. ファイルを指定してビルド
- 実行ファイル名の指定なし、存在しないソースファイル名を使った指定はエラー
- toy_share.cpp(シェアの生成と復元だけ確認)をビルドしたいときは以下
```bash
$ make toy_share
```

5. 実行
- 実行ファイルがtoy_shareのときは以下
```bash
$ ./bin/toy_share
```