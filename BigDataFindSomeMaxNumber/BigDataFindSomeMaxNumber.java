package com.learn.others;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;
//在FileIODemo生成的文件中找出前25大的数
//后续可以考虑引用多线程进行优化，可以考虑CountDownLatch
public class BigDataFindSomeMaxNumber {
	private static final int MAX_LINE_PER_PROCESS = 25;
	private static final int RANK_OF_NUMBER = 5;
	private static final String FILE_PATH_PREFIX = "xxxx\\";
	private static final String FILE_PATH_SUFFIX = ".txt";
	
	private static String []arrSamllFilePath = new String[FileIODemo.COUNT_OF_NUMBER / MAX_LINE_PER_PROCESS];
	
	private static int []arrAllData = new int[FileIODemo.COUNT_OF_NUMBER + 1];
	
	static void initializeArr(int a[]) {
		for (int i = 0; i < a.length; i++) {
			a[i] = 0;
		}
	}
	
	//维护小顶堆
	static void heapAdjust(int a[],int inode,int length){
		int child = length;
		//建的时候是从底向上建，就能保证所有父节点都大于其子节点。排序的时候因为都是和最底下的叶子节点交换，所以便需要从顶向下维护堆
		for(int i = inode ; 2*i<=length ; i = child){
			if( (2*i+1) <= length){
				child = a[2*i]<a[2*i+1]?(2*i):(2*i+1);
			}else if((2*i) <= length){
				child = 2*i;
			}
			//小顶堆，父节点不能大于子节点
			if(a[i] > a[child]){
				int tmp = a[i];
				a[i] = a[child];
				a[child] = tmp;
			}else{
				break;
			}
		}
		
	}
	
	static void writeArr2File(int []arr, int start, int end, String filePath) {
		StringBuffer sBuffer = new StringBuffer("");
		try { // 防止文件建立或读取失败，用catch捕捉错误并打印，也可以throw

			/* 写入Txt文件 */
			File writename = new File(filePath); // 相对路径，如果没有则要建立一个新的output。txt文件
			writename.createNewFile(); // 创建新文件
			BufferedWriter out = new BufferedWriter(new FileWriter(writename));
			for (int i = start; i <= end; i++) {
				sBuffer.append(arr[i] + "\r\n");
			}
			out.write(sBuffer.toString()); // \r\n即为换行
			out.flush(); // 把缓存区内容压入文件
			out.close(); // 最后记得关闭文件
		
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	static void generateTmpFilePath(String []arrFilePath) {
		for (int i = 0; i < arrFilePath.length; i++) {
			arrFilePath[i] = FILE_PATH_PREFIX + i  + FILE_PATH_SUFFIX;
		}
	}
	
	static String arr2String(int []arr) {
		String s = "";
		for (int i = 0; i < arr.length; i++) {
			s = s+ arr[i] + ",";
		}
		return s;
	}
	
	private static void splitAndProcessBigFile(String filePath) {
		int []arrData = new int[RANK_OF_NUMBER+1];

		initializeArr(arrData);
		try { // 防止文件建立或读取失败，用catch捕捉错误并打印，也可以throw

			/* 读入TXT文件 */
			File filename = new File(filePath); // 要读取以上路径的input。txt文件
			InputStreamReader reader = new InputStreamReader(new FileInputStream(filename)); // 建立一个输入流对象reader
			BufferedReader br = new BufferedReader(reader); // 建立一个对象，它把文件内容转成计算机能读懂的语言
			String line = "";
			int nIter = 1;
			int nFileIter = 0;
			line = br.readLine();
			while (line != null) {
				int num = Integer.parseInt(line);
				arrAllData[nIter] = num;
				if (num > arrData[1]) {
					arrData[1] = num;
					heapAdjust(arrData, 1, arrData.length-1);	
				}
				if (nIter % MAX_LINE_PER_PROCESS==0) {
					writeArr2File(arrData, 1, arrData.length-1, arrSamllFilePath[nFileIter]);
					initializeArr(arrData);
					
					nFileIter++;
				}
				nIter += 1;
				line = br.readLine(); // 一次读入一行数据
			}
			br.close();
			reader.close();
//			System.out.println(nIter);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private static void putFileDataIntoArr(String filePath, int []arr, int start, int end) {
		try { // 防止文件建立或读取失败，用catch捕捉错误并打印，也可以throw
			/* 读入TXT文件 */
			File filename = new File(filePath); // 要读取以上路径的input。txt文件
			InputStreamReader reader = new InputStreamReader(new FileInputStream(filename)); // 建立一个输入流对象reader
			BufferedReader br = new BufferedReader(reader); // 建立一个对象，它把文件内容转成计算机能读懂的语言
			String line = "";
			int nIter = start;
			
		
			line = br.readLine();
			while (line != null) {
				int num = Integer.parseInt(line);
				if (nIter <= end) {
					arr[nIter] = num;
				}
				nIter++;
				line = br.readLine(); // 一次读入一行数据
			}
			br.close(); // 最后记得关闭文件
			reader.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	static void heapSort(int []arr) {
		//从最后一个非叶子节点开始维护堆，因为是完全二叉树，所以最后一个非叶子节点之前的节点都是非叶子节点
		for(int i=arr.length-1/2;i>0;i--){
			heapAdjust(arr, i , arr.length - 1);
		}
		for(int i=arr.length-1 ; i> 1;i--) {
			int tmp = arr[i];
			arr[i] = arr[1];
			arr[1] = tmp;
			heapAdjust(arr, 1, i-1);
		}
	}
	
	public static void main(String args[]) {
	
		generateTmpFilePath(arrSamllFilePath);
		splitAndProcessBigFile(FileIODemo.PROCESS_FILE_PATH);
		
		int []arrData = new int[arrSamllFilePath.length * RANK_OF_NUMBER +1];
		for (int i = 0; i < arrSamllFilePath.length; i++) {
			putFileDataIntoArr(arrSamllFilePath[i], arrData, i*5+1, (i+1) * RANK_OF_NUMBER);
		}
//		System.out.println(arr2String(arrData));
		heapSort(arrData);
		heapSort(arrAllData);
		System.out.println(arr2String(arrAllData));
		System.out.println(arr2String(arrData));
	}
}
