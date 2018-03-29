package fri_median;

public class Median {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] num=new int[10];
		for(int i=0;i<10;i++)
			{
			num[i]=(int)(Math.random()*100);
			System.out.print(num[i]+"\t");
			}
		System.out.println("\nmedian:"+median(num));
		
	}
	public static int median(int []nums){  
        if(nums.length==0)  
            return 0;  
        int start=0;  
        int end=nums.length-1;  
        int index=partition(nums, start, end);  
        if(nums.length%2==0){  
            while(index!=nums.length/2-1){  
                if(index>nums.length/2-1){  
                    index=partition(nums, start, index-1);  
                }else{  
                    index=partition(nums, index+1, end);  
                }  
            }  
        }else{  
            while(index!=nums.length/2){  
                if(index>nums.length/2){  
                    index=partition(nums, start, index-1);  
                }else{  
                    index=partition(nums, index+1, end);  
                }  
            }  
        }  
        return nums[index];  
    }
	
	private static int partition(int nums[], int start, int end){  
        int left=start;  
        int right=end;  
        int pivot=nums[left];  
        while(left<right){  
            while(left<right&&nums[right]>=pivot){  
                right--;  
            }  
            if(left<right){  
                nums[left]=nums[right];  
                left++;  
            }  
            while(left<right&&nums[left]<=pivot){  
                left++;  
            }  
            if(left<right){  
                nums[right]=nums[left];  
                right--;  
            }  
        }  
        nums[left]=pivot;  
        return left;  
    }  

}
