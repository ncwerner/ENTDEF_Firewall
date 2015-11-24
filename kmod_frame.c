/* very basic kernel mod test 
 * outputs the print statements to
 * /var/log/message */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfliter.h>
#include <linux/netfliter_ipv4.h>
#include <linux/skbuff.h>
#include <arpa/inet.h>

#ifndef __KERNEL__
#define __KERNEL__
#endif 

#ifndef MODULE
#define MODULE
#endif

#define PORT 23
#define SADDR "192.168.0.1"
#define DADDR "192.168.0.4"
#define MACHINE_A "192.168.0.2"
#define MACHINE_B "192.168.0.3"
#define SSH_ALLOW "192.168.0.5"

//Struct holding set of hook function options
static struct nf_hook_ops nfho;

static struct* tcphdr tcp_header;
static struct* iphdr ip_hdr;

//function to be called by hook
    unsigned int hookf(unsigned int hooknum, struct sk_buff** skb, const struct net_device* in, const struct net_device* out, int (*okfn)(struct sk_buff *)){
      //Handles all null buffer cases
      if(!(*skb)) return NF_ACCEPT;

      //Carries all ip header information
      ip_hdr = (struct iphdr*)skb_network_header(sock_buff);
      
      //Carries all tcp packet info
      tcp_hdr = (struct tcphdr*)skb_transport_header(sock_buff);
      
      
      //Blocks telnet from machine A and B
      //Two rules bitches
      else if(tcp_hdr->source == PORT &&
	      ((strcmp(inet_ntoa(ipheader->saddr), MACHINE_A)) ||
	       (strcmp(inet_ntoa(ipheader->saddr), MACHINE_B)))
	      )
	return NF_DROP;
      
      //Blocking a particular IP from an outside web address
      else if((strcmp(inet_ntoa(ipheader->daddr), DADDR)) &&
	      (strcmp(inet_ntoa(ipheader->saddr), SADDR))
	      )
	return NF_DROP;

      //Block ssh traffic to everything except one IP
      if(!((strcmp(inet_ntoa(ipheader->daddr), SSH_ALLOW))) &&
	 tcp_hdr->dest == 22)
	return NF_DROP;

      //Block IP address range
      
      printk(KERN_INFO "packet accepted\n");
      return NF_ACCEPT;
    }

int init_module(void) {

  nfho.hook = hookf;
  nfho.hooknum = NF_IP_PRE_ROUTING;
  nfho.pf = PF_INET;
  nfho.priority = NF_IP_PRI_FIRST;
  nf_register_hook(&nfho);
  
    printk(KERN_INFO "Kernel mod init run\n");

    /*
      Use netfliter and register a hook function which returns 
      a NF_ action code
      Each hook must have a corresponding struct nf_hook_ops that 
      holds the hook and all other option info needed
      must be declared outside init_module and fields set w/in
      init_module
      Declared static to restrict it to this particular file
    */

    
    
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Kernel mod removed\n");
    /*
      Unregister hook
    */
}
