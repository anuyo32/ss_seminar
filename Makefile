# 変数名参考：https://qiita.com/harinez2/items/0d25eabdc6dae66e7bee

TARGET = ./bin/$@
SRCDIR = ./src
SRC    = $(shell find $(SRCDIR) -name $@".cpp")
CXX    = g++

# https://triple-four.hatenablog.com/entry/20210623/1624458051
# いろいろな警告とエラーを有効(全てではない)
CFLAGS = -Wall -Wextra

%: $(SRC)
	$(CXX) $(CFLAGS) -o $(TARGET) $(SRC)
