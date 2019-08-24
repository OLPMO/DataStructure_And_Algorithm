package com.learn.others;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.util.Random;

//随机生成100个1000-9999的数，并将其写入文件
public class FileIODemo {
	public static final String PROCESS_FILE_PATH = "xxx\\output.txt";
	public static final int COUNT_OF_NUMBER = 100;
	public static void main(String args[]) {
		
		int max = 9999;
		int min = 1000;
		Random random = new Random();
		StringBuffer sBuffer = new StringBuffer("");
		
		for (int i = 0; i < COUNT_OF_NUMBER; i++) {
			int s = random.nextInt(max) % (max - min + 1) + min;
			sBuffer.append(Integer.toString(s) +  "\r\n");
		}

		try { // 防止文件建立或读取失败，用catch捕捉错误并打印，也可以throw

			/* 写入Txt文件 */
			File writename = new File(PROCESS_FILE_PATH); // 相对路径，如果没有则要建立一个新的output.txt文件
			writename.createNewFile(); // 创建新文件
			BufferedWriter out = new BufferedWriter(new FileWriter(writename));
			out.write(sBuffer.toString()); // \r\n即为换行
			out.flush(); // 把缓存区内容压入文件
			out.close(); // 最后记得关闭文件

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
